#include "SlackBot.h"

SlackBot::SlackBot():Tool(){}


bool SlackBot::Initialise(std::string configfile, DataModel &data){
  
  m_data= &data;

  if(m_tool_name=="") m_tool_name="SlackBot";
  
  // get tool config from database
  std::string configtext;
  bool get_ok = m_data->postgres_helper.GetToolConfig(m_tool_name, configtext);
  if(!get_ok){
    Log(m_tool_name+" Failed to get Tool config from database!",0,0);
    //return false;
  }
  // parse the configuration to populate the m_variables Store.
  std::stringstream configstream(configtext);
  if(configtext!="") m_variables.Initialise(configstream);
  
  // allow overrides from local config file
  if(configfile!="")  m_variables.Initialise(configfile);

  // get webhook
  m_variables.Get("webhook",webhook);

  //m_variables.Print();

  CURL *curl;
  CURLcode res;
  
  std::stringstream tmp;
  
  tmp<<"payload={\"text\":\"Run Number:"<<m_data->run<<", Sub Run Number:"<<m_data->subrun<<", Run Type:"<<m_data->RunType<<", Status:"<<"Run started\"}";
  //std::cout<<tmp.str()<<std::endl;
  
  try{  
    /* In windows, this will init the winsock stuff */ 
    curl_global_init(CURL_GLOBAL_ALL);
    
    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
      /* First set the URL that is about to receive our POST. This URL can
	 just as well be a https:// URL if that is what should receive the
	 data. */ 
      curl_easy_setopt(curl, CURLOPT_URL, webhook.c_str());
      /* Now specify the POST data */ 
      std::string field;
      field=tmp.str();
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS,field.c_str());
      
      /* Perform the request, res will get the return code */ 
      res = curl_easy_perform(curl);
      /* Check for errors */ 
      if(res != CURLE_OK)
	fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
      
      /* always cleanup */ 
      curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
  }
  catch(...){
    Log("Slack send error",0,m_verbose);    

  }
  /*
  m_data= &data;
  pid_t  pid;

  //  pid = fork();
  // if (pid == 0){
  // std::cout<<"child started"<<std::endl;
  std::stringstream tmp;
  tmp<<"curl -k -X POST --data-urlencode 'payload={\"text\":\"Run Number:"<<m_data->RunNumber<<", Sub Run Number:"<<m_data->SubRunNumber<<", Run Type:"<<m_data->RunType<<", Status:"<<"Run started\"}' "<< webhook.c_str();
  //  std::cout<<tmp.str()<<std::endl;
  system("ls -al");
  */
  //exit(0);
  //}

  //Ben need to replace
  //  m_data->InfoTitle="SlackBotVariables";
  // m_variables>>m_data->InfoMessage;
  // m_data->GetTTree("RunInformation")->Fill();
  //m_data->Stores["RunInformation"]->Set("SlackBot",m_variables);

  return true;
}


bool SlackBot::Execute(){
  //if(m_data->Restart==1)Finalise();
  //else if(m_data->Restart==2)Initialise("",*m_data);

  return true;
}


bool SlackBot::Finalise(){

  std::stringstream tmp;
  tmp<<"payload={\"text\":\"Run Number:"<<m_data->run<<", Sub Run Number:"<<m_data->subrun<<", Run Type:"<<m_data->RunType<<", Status:"<<"Run ended, "<<m_data->NumEvents<<" events\"}";

  try{
    
    CURL *curl;
    CURLcode res;
    
    //  std::cout<<tmp.str()<<std::endl;
    
    
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
      /* First set the URL that is about to receive our POST. This URL can
	 just as well be a https:// URL if that is what should receive the
	 data. */
      curl_easy_setopt(curl, CURLOPT_URL, webhook.c_str());

      std::string field;
      field=tmp.str();
      /* Now specify the POST data */
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, field.c_str());
      
      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);
      /* Check for errors */
      if(res != CURLE_OK)
	fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
      
      /* always cleanup */
      curl_easy_cleanup(curl);
    }
    curl_global_cleanup();    
    
  }
  catch(...){
    Log("Slack send error",0,0);
  }
  
 
  return true;
}
