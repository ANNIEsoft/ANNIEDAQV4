#include "CardData.h"

void bencleanup (void *data, void *hint) {
  //  free (data);
}
void bencleanupb (void *data, void *hint) {
  if (hint!=0){
    std::vector<CardData>* tmp=reinterpret_cast<std::vector<CardData>* >(hint);
    delete tmp;
  }
}

CardData::~CardData(){

}

int  CardData::Send(zmq::socket_t *socket, int flag, std::vector<CardData>* hint){
  int ret=1;  

  //std::cout<<"d0 flag ="<<flag<<std::endl;
  //zmq::message_t ms1(&LastSync,sizeof LastSync, bencleanup);
  // std::cout<<"d0.1"<<std::endl;  
zmq::message_t ms2(&SequenceID,sizeof SequenceID, bencleanup);
 //std::cout<<"Sequence ID="<< SequenceID<<std::endl;

//  zmq::message_t ms3(&StartTimeSec,sizeof StartTimeSec, bencleanup);
  //std::cout<<"d0.3"<<std::endl;

//  zmq::message_t ms4(&StartTimeNSec,sizeof StartTimeNSec, bencleanup);
  //std::cout<<"d0.4"<<std::endl;

  //zmq::message_t ms5(&StartCount,sizeof StartCount, bencleanup);
  //std::cout<<"triggercounts snd size check = "<<triggerCounts.size()<<" card = "<< CardID<<std::endl;
  //std::cout<<"data.size = "<<Data.size()<<std::endl;
  //std::cout<<"d0.5"<<std::endl;

  //zmq::message_t ms6(&(triggerCounts.at(0)), sizeof(uint64_t)*triggerCounts.size(), bencleanup);
  //std::cout<<"d0.6"<<std::endl;

  // zmq::message_t ms7(&(Rates.at(0)), sizeof(uint32_t)*Rates.size(), bencleanup); 
  //std::cout<<"d0.7"<<std::endl;
  
  zmq::message_t ms1(&CardID,sizeof CardID, bencleanup);
  //std::cout<<"CardID="<<CardID<<std::endl;

  // std::cout<<"CardID = "<<CardID<<std::endl;
  //zmq::message_t ms9(&channels,sizeof channels, bencleanup);
  //std::cout<<"d0.9"<<std::endl;

  //  zmq::message_t ms10(&buffersize,sizeof buffersize, bencleanup);
  //std::cout<<"d0.10"<<std::endl;

  // std::cout<<"buffersize = "<<buffersize<<std::endl;
  //std::cout<<"fullbuffsize = "<<fullbuffsize<<std::endl;
  //zmq::message_t ms11(&eventsize,sizeof eventsize, bencleanup);
  //std::cout<<"d0.11"<<std::endl;

  zmq::message_t ms3(&FirmwareVersion,sizeof FirmwareVersion, bencleanup);        
  //std::cout<<"FirmwarVersion="<<FirmwareVersion<<std::endl; 
  ret *= socket->send(ms1,ZMQ_SNDMORE);
  ret *= socket->send(ms2,ZMQ_SNDMORE);
  ret *= socket->send(ms3,ZMQ_SNDMORE);


  //std::cout<<"d0.11b "<<Data.size()<<std::endl;

  size = Data.size();
  //std::cout<<"d0.11c "<<size<<std::endl;
  zmq::message_t ms4(&size,sizeof size, bencleanup);
  //std::cout<<"d0.11d "<<size<<std::endl;
  if(size>0){
    socket->send(ms4,ZMQ_SNDMORE);
    zmq::message_t ms5(&(Data.at(0)), sizeof(uint32_t)*Data.size(), bencleanup);
    //std::cout<<"d0.12"<<std::endl;
    ret *= socket->send(ms5,ZMQ_SNDMORE);
    //    std::cout<<"Data.at(0): Data.at(size-1)="<<Data.at(0)<<" : "<<Data.at(size-1)<<std::endl;

    // for(int k=0;k<size;k++){
      //std::cout<<"Data["<<k<<"]="<<Data.at(k)<<std::endl;
    // }
  }
  else{
    //std::cout<<"d0.13"<<std::endl;
    ret *= socket->send(ms4,ZMQ_SNDMORE);
  }
  
  
  //  std::cout<<"data.size = "<<Data.size()<<std::endl;
  // std::cout<<"data.size2 = "<<Data.size()*sizeof(uint16_t)<<std::endl;
  
   zmq::message_t ms6(&FIFOstate,sizeof FIFOstate, bencleanupb,hint);
  

//std::cout<<"d1"<<std::endl;  
  /*  for (int i=0;i<Data.size();i++){
      
      if(Data.at(i)==0)    std::cout<<" data.at("<<i<<")="<<Data.at(i);
      }
      std::cout<<std::endl;
  */
  //zmq::message_t ms8(&fullbuffsize,sizeof fullbuffsize, bencleanup);
  
  
  ret *= socket->send(ms6,flag);
  //std::cout<<"FIFO = "<<FIFOstate<<std::endl;
  //  socket->send(ms5,ZMQ_SNDMORE);
  //socket->send(ms6,ZMQ_SNDMORE);                              
  //socket->send(ms7,ZMQ_SNDMORE);
  //socket->send(ms8,ZMQ_SNDMORE);
  //socket->send(ms9,ZMQ_SNDMORE);
  // socket->send(ms10,ZMQ_SNDMORE);
  // socket->send(ms11,ZMQ_SNDMORE);
  // socket->send(ms12);
  //std::cout<<"d2"<<std::endl;
  //std::cout<<" ben 1"<<std::endl;
  //for(int i=0;i<channels;i++){
  //zmq::message_t ms(&PMTID[0],&PMTID[channels]);
  // zmq::message_t ms(PMTID,sizeof(int)*channels,bencleanup);
  //zmq::message_t ms(&PMTID[i],sizeof PMTID[i], bencleanup);
  // std::cout<<" ben 2"<<std::endl;
  
  //socket->send(ms);
  //  }
  //std::cout<<" ben 3 "<< (sizeof(Data)/sizeof(uint16_t)) <<std::endl;

  //for(int i=0;i<fullbuffsize;i++){
  // Data[i];
  // }
  //std::cout<<"sizeof *Data "<<sizeof *Data <<std::endl;
  
  //std::cout<<"&Data[0] "<<&Data[0]<<std::endl;
  //std::cout<<"&Data[fullbuffsize] "<<&Data[fullbuffsize]<<std::endl;
  
  //std::vector<uint16_t> v(Data, Data + sizeof Data / sizeof Data[0]);
  //zmq::message_t mss(v.begin(),v.end());
  //    zmq::message_t mss(Data, sizeof(uint16_t)*fullbuffsize, bencleanup); 
  
  //std::cout<<" ben 4"<<std::endl;
  
  //zmq::message_t ms(&Data[i],sizeof Data[i], bencleanup);
  // socket->send(mss);
  //std::cout<<" ben 5"<<std::endl;
  
  //}
  
  //socket->send(ms6);

  return ret;  
  
}

void CardData::Receive(zmq::socket_t *socket){
  /*
  int more;                                                                   
  size_t more_size = sizeof (more);                                           
  // Receive->getsockopt(ZMQ_RCVMORE, &more, &more_size);                     
                                                                                
  zmq::message_t message;                                                     
  //        std::cout<<"about to get message"<<std::endl;                     
                                                                                
  while (true){                                
    IF(Receive->recv(&message)){   
  */  
   /*
  zmq::message_t message;

  socket->recv(&message);
  LastSync=*(reinterpret_cast<uint64_t*>(message.data()));
  socket->recv(&message);
  SequenceID=*(reinterpret_cast<int*>(message.data()));
  socket->recv(&message);
  StartTimeSec=*(reinterpret_cast<int*>(message.data()));
  socket->recv(&message);
  StartTimeNSec=*(reinterpret_cast<int*>(message.data()));
  socket->recv(&message);
  StartCount=*(reinterpret_cast<uint64_t*>(message.data()));
  socket->recv(&message);
  //std::cout<<"triggercounts rec size check = "<<message.size()<<std::endl;
  triggerCounts.resize(message.size());
  triggerNumber=message.size();
  std::memcpy(&triggerCounts[0], message.data(), message.size());
  socket->recv(&message);
  Rates.resize(message.size());
  std::memcpy(&Rates[0], message.data(), message.size());
  socket->recv(&message);
  CardID=*(reinterpret_cast<int*>(message.data()));
  std::cout<<"CardID = "<<CardID<<std::endl;
  socket->recv(&message);
  channels=*(reinterpret_cast<int*>(message.data()));
  socket->recv(&message);
  buffersize=*(reinterpret_cast<int*>(message.data()));
  socket->recv(&message);
  eventsize=*(reinterpret_cast<int*>(message.data()));
  socket->recv(&message);
  Data.resize(message.size());
  fullbuffsize=message.size();
  std::memcpy(&Data[0], message.data(), message.size());
  */  
      /*
      Receive->getsockopt(ZMQ_RCVMORE, &more, &more_size);                    
          
}
                                                        
    if(more==0) break;
      */


}
