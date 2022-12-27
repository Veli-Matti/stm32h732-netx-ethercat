
NetPROXY Host API {#mainpage}
=============================

\ref disclaimer "Exclusion of Liability for this demo software"

The netPROXY Host API is used for accessing the netPROXY runtime over the HIF DPM. This implementation uses the 
cifX API to access the DPM. 

\image html Host_API_Overview.png

API overview
------------
 - \ref npxhost_basic_doc
 - \ref npxhost_sync_doc
 - \ref npxhost_async_doc
 






 
\defgroup npxhost_basic_doc Basic API functions
The functions in this section are used for initialization the netPROXY Host API and opening the desired channel.
 
\defgroup npxhost_sync_doc API for synchron object access 
netPROXY API functions, which will block until the response is available or a timeout issue occurs.
 
\defgroup npxhost_async_doc API for asynchron object access 
netPROXY API functions, which will not block.  
