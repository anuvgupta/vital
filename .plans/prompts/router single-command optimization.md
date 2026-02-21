 Current flow:                                                                                                                                                                                                                        - Simple/question: Router (no schema, ~512 tokens) → Preset LLM (full schema) = 2 calls always                                                                                                                                     
  - Multi-action: Router → N × Preset LLM = 1 + N calls                                                                                                                                                                              
  
  If router answers directly:
  - Simple/question: Router answers directly = 1 call (faster, cheaper)
  - Multi-action: Router → N × Preset LLM = 1 + N calls (unchanged)

  The catch: The router currently has no preset schema, no synthesizer cookbook, and no current preset JSON. So it can answer general Vital questions, but it cannot:
  - Generate JSON diffs (no schema)
  - Answer preset-specific questions like "what's my filter set to?" (no preset context)
  - Handle even simple single-action modifications

  To make the router handle single actions, you'd need to give it the full schema + preset JSON — which makes the router call just as expensive as the current preset LLM call. At that point you're not saving anything for
  multi-action requests (the router is now heavy), and only saving one call for single-action.

  The real cost right now is actually the opposite — the router adds latency to every request, including simple ones that didn't need routing. A simple "increase filter cutoff" now takes 2 serial API calls instead of 1.

  So the honest tradeoff is: do you want to optimize for simple requests (skip the router entirely for obvious single commands) or complex requests (router adds value by splitting)? Right now every request pays the router tax.
