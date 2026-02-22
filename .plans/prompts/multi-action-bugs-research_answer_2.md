  1. Conversation history — polluted or clean?                                 
                                                                               
  Still polluted with raw JSON diffs. Look at the assistant entries:                                                                                            assistant: {"settings":{"osc_2_on":1.0}}                                       assistant: {"settings":{"osc_3_on":1.0}}                                     
  assistant: {"settings":{"sample_on":1.0,"filter_1_on":1.0,...}}
  assistant: {"settings":{"env_1_release":1.2}}
  assistant: {"settings":{"reverb_on":1.0,...wavetables:[...]...}}   ← this one
   is huge

  Change 1 (the JSON fence fix) isn't catching these because the LLM is        
  returning raw JSON without code fences. The system prompt says "No
  explanation, no markdown code fences, no commentary — just the raw JSON      
  diff." So when the LLM obeys that instruction, extractFenceContent finds no  
  fence (fenceStart < 0), returns with both textOut and jsonOut empty, and the 
  else branch at line 462 stores the entire responseText — the raw JSON.       

  The fix only works when the LLM wraps JSON in fences (the mixed text+JSON    
  case). For pure JSON responses (the most common case), it does nothing.      

  Fix needed: After extractFenceContent, also try to detect raw JSON (starts   
  with {, contains "settings") and replace with "(preset updated)".

  2. Token size & content relevance

  Request sizes:
  - Router calls: 3-12K chars (reasonable — system prompt + history + tools)   
  - sendMessage calls: 79-88K chars (10-13K input tokens)
  - Sound design translation: 31-34K chars (~12K input tokens)

  The 79-88K sendMessage requests are dominated by:
  - System prompt + schema: ~17.5K tokens (cached, good)
  - Preset JSON: ~7-8K chars per request — injected fresh each time, reasonable
   since it's ephemeral
  - History with leaked JSON: The wavetable change response at line 724 alone  
  is ~600+ chars of JSON stored as "assistant" content. Multiply by several    
  such entries.

  Uncaught JSON diffs in history: YES — every single assistant response that   
  was pure JSON (no fences) is stored verbatim. Lines 692, 700, 708, 716, 724  
  all show raw JSON diffs in the conversation history. The wavetable one at    
  line 724 is particularly large.

  3. Preset size in subsequent requests

  The preset JSON block (injected as ephemeral user message) is consistently   
  ~7-8K chars. This is the full preset minus base64 data (which is correctly   
  stripped to "(base64 data removed)"). This is reasonable and expected — it's 
  needed for context.

  4. Message size growth during sound design / multi-action

  Looking at the sendMessage request sizes during the sound design multi-action
   flow:
  - Sub-action 1: 82,215 chars
  - Sub-action 2: 83,523 chars (+1,308)
  - Sub-action 3: 83,966 chars (+443)
  - Sub-action 4: 84,385 chars (+419)

  Growth per sub-action is ~400-1300 chars — that's the sub-action user prompt 
  + assistant response being added to history. This is reasonable now that the 
  full translation isn't in there.

  The sound design translation at line 728 shows "make this an 808 nbass"      
  correctly stored as original user message. No translation text visible.      
  Multi-action history isolation is working.

  5. Why is JSON being printed in the result?

  The raw JSON is showing up in the chat because the LLM returns pure JSON     
  without code fences (exactly as the system prompt instructs for
  modification-only requests). The full_interface.cpp parsing flow tries to    
  parse the response as JSON — and it succeeds, applies the patch, and shows a 
  completion phrase. So the preset gets applied correctly.

  But the history storage at line 460-463 doesn't catch this case. It only     
  catches JSON inside code fences. When there's no fence, the full JSON string 
  gets stored as the "assistant" message in history.

  Root cause summary: The extractFenceContent approach only handles the "text +
   fenced JSON" case. For pure JSON responses (the most common path), there's  
  no fence to detect, so the JSON leaks into history unchanged.