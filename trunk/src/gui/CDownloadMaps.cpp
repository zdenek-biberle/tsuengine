#include "CDownloadMaps.h"


#include <exception>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "CBaseEngine.h"
#include "datatypes.h"
#include "CButton.h"

CStatusOverlay::CStatusOverlay(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size)
{
  setFgColor(rgba(0.7, 0.7, 0.7, 0.7));
  setBgColor(rgba(0.1, 0.1, 0.1, 0.7));

}

void CStatusOverlay::draw(){
  drawVerticalGradient(0, 0, getW(), getH(), fgColor, bgColor);
}

void CStatusOverlay::closeOverlay(int){
  setVisible(false);
}

CDownloadMaps::CDownloadMaps():
  CCenteredWindow(vec2d(500,350), "Stahování map")
{
  json::mValue mapList;
  m_dataDownloadStatus = DDS_NONE;
  try{


    net::http::client::request request("http://tsuengine.php5.cz/getMapList.php");
    request << net::header("Connection", "close");
    net::http::client::response rsp = net::http::client().get(request);
    if(status(rsp) != 200) throw 1;
    std::string s = body(rsp);
    //engine->log(s);
    json::read(s, mapList);
  }catch(...){
    CText* tmp = new CText(vec2d(20, 50.), getSize()-vec2d(40., 70.), 14., CLabel::ALIGN_CENTER);
    tmp->setText("Nebylo možné získat seznam dat");
    addChild(tmp);
    return;
  }

  m_list = new CListBox(vec2d(20,50), vec2d(260, 280));

    m_list->addListener(makeCListenerMemberFn(0,this,&CDownloadMaps::setDescription));
    addChild(m_list);

    m_descText = new CText(vec2d(300., 50), vec2d(160, 280), 14);
    m_descText->setText("Vyberte mapu ke stažení");
    addChild(m_descText);

    CButton* tmp = new CButton(vec2d(300, getH()-45.), vec2d(100, 25), "Stáhnout");
    tmp->addListener(makeCListenerMemberFn(0, this, &CDownloadMaps::doDownload));
    addChild(tmp);

  m_overlay = new CStatusOverlay(vec2d(1., 31.), getSize() - vec2d(2., 32.));
  m_overlay->setVisible(false);
  addChild(m_overlay);

  m_overlayButton = new CButton(m_overlay->getSize()-vec2d(120., 45.), vec2d(100., 25. ), "Zavřít");
  m_overlayButton->setVisible(false);
  m_overlay->addChild(m_overlayButton);
  m_overlayButton->addListener(makeCListenerMemberFn(0, m_overlay, &CStatusOverlay::closeOverlay));

  m_statusMessage = new CText(vec2d(20., 20.), m_overlay->getSize()-vec2d(40., 40.), 14);
  m_overlay->addChild(m_statusMessage);

  BOOST_FOREACH(const json::mValue& map, mapList.get_array()){
    engine->log("adding item");
    m_list->addItem(map.get_obj().find("name")->second.get_str());
    m_descList.push_back(map.get_obj().find("desc")->second.get_str());
  }



  //boost:network::body_directive
}

void CDownloadMaps::setDescription(int){
  m_descText->setText(m_descList[m_list->getSelectedItem()]);
}

void CDownloadMaps::doDownload(int){
  try{
    if(m_dataDownloadStatus == DDS_NONE){
      m_dataDownloadStatus = DDS_FILELIST;
      AsyncClient::request request("http://tsuengine.php5.cz/data/dataLists/"+m_list->getSelectedString());
      request << net::header("Connection", "close");
      engine->net->response = engine->net->client.get(request);
      m_overlay->setVisible(true);
      m_statusMessage->setText("Stahuji seznam souborů");
      m_fileList.clear();
      m_lastFile = -1;
    }
  }catch(std::exception& e){
    m_statusMessage->setText(e.what());
  }catch(...){
    m_statusMessage->setText("Nebylo možné získat seznam souborů");
  }
}

void CDownloadMaps::think(){
  try{
    if(m_dataDownloadStatus != DDS_NONE){
      if(ready(engine->net->response)){
        if(status(engine->net->response) == 200){
          String data = body(engine->net->response);
          if(m_dataDownloadStatus == DDS_FILELIST){
            json::mValue val;
            json::read(data, val);
            const json::mArray& files = val.get_obj().find("files")->second.get_array();
            m_fileList.reserve(files.size());
            BOOST_FOREACH(const json::mValue& file, files){
              if(!boost::filesystem::exists(file.get_str())){
                m_fileList.push_back(file.get_str());
              }
            }
            m_lastFile = -1;
            downloadNextFile();
          }else if(m_dataDownloadStatus == DDS_FILES){
            boost::filesystem::ofstream file(m_fileList[m_lastFile], std::fstream::out | std::fstream::binary);
            file<<data;
            file.close();
            downloadNextFile();
          }
        }
      }
    }
  }catch(std::exception& e){
    m_statusMessage->setText(e.what());
  }catch(...){
    m_statusMessage->setText("Nebylo možné stáhnout soubor");
  }
}

void CDownloadMaps::downloadNextFile(){
  engine->log("Downloading next file");
  m_lastFile++;
  if(m_lastFile >= m_fileList.size()){
    m_dataDownloadStatus = DDS_NONE;
    //m_overlay->setVisible(false);
    finishDownload("Stahování dokončeno.");
  }else{
    m_dataDownloadStatus = DDS_FILES;
    AsyncClient::request request("http://tsuengine.php5.cz/data/"+m_fileList[m_lastFile]);
    request << net::header("Connection", "close");
    engine->net->response = engine->net->client.get(request);
    m_statusMessage->setText("Stahuji soubor "+m_fileList[m_lastFile]+sformat("(%d/%d)", m_lastFile+1, m_fileList.size()));
  }
}

void CDownloadMaps::finishDownload(const String& text){
  m_statusMessage->setText(text);
  m_overlayButton->setVisible(true);
}
