action items for fixing high input token coist:

- for item #3 and #4 and #5 - lets first investigate if anything is polluting the convo history ie old json, old presets, whole result from preset generation calls including json results (these dont need to be included) - the point of conversation history is to just track the last 20 messages sent by user and only include system response if there is any actual response, not to track every json change. if we need to reduce convo size ffrom 20 to 15 we can, but id prefer not to change that , and instead just make sure only relevant tokens are going into the convo history. it really souldnt be that big, the users requests dont take up much space. i also think if the convo is small, it should eb sent to the translator, router, and all calls because its not big at all and people often send a command like "make it louder" in which case you need context o the last fe wmessages even for sound design and router calls.




lets fix #1 for sure using your suggestion. lets also double check to make  
  sure there are no other bugs with conversation hsitory regarding json - we  
  shiould not be storing ANY json in conversation history. user messages and  
  natural language responses from llm are fine. store only natural lanagueg   
  part of responses form llm that include both natural language and json      
  diff. are we clear? lets also implement a logging function on every request 
  that we send to claude, we add a line to a running file tracking all       
  requests and repsonses. we should include the full input, the full output,  
  and the lenghts of each in # characters (and tokens if we get that info     
  from api). i can later share this with you to analyze the fixes. for issue  
  #2, i think we can keep the original long user message or sound design      
  translation result in permanent convo history. what we don't need ot keep   
  in permanent convi hsitory is the individual sub-action prompts, as you     
  mentioned. thses still ned to be in convo history when we call claude for   
  the sub-action, but they dont need ot be in conv history for subsequent     
  user prompts. again if there is any response from llm that is natural       
  language, even for a sub-action, we can keep that in convo history. are we  
  clear? let me knwo if you have any questions. finall, for issue #3, its not 
  a problem. lets also complete these action items from original issue list  
  above: - switch router call to sonnet 4.5 - this takes care of original
  item #1. also ensure router call isnt including preset json, response json,  
  or anything unnecessary
  - remove the sound design cookbook for now - this takes care of original
  item #2 - (i already renamed it to SOUND_DESIGN_GUIDE.md and emptied it for  
  now, you now just have to update the name in code)