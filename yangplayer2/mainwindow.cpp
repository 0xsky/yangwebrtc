﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "yangutil/sys/YangSocket.h"
#include <yangutil/sys/YangLog.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_centerWdiget=new QWidget(this);
    m_vb=new QVBoxLayout();

    setCentralWidget(m_centerWdiget);
    m_centerWdiget->setLayout(m_vb);
    m_vb->setMargin(0);
    m_vb->setSpacing(0);
    m_videoWin=new YangPlayWidget(this);


    m_hb1=new QHBoxLayout();
    m_hb2=new QHBoxLayout();
    m_hb1->addWidget(ui->m_l_url);
    m_hb1->addWidget(ui->m_url);
    m_hb1->addWidget(ui->m_b_play);
    //m_hb1->addWidget(ui->m_b_rtc);
    m_hb2->addWidget(m_videoWin);
    m_vb->addLayout(m_hb1);
    m_vb->addLayout(m_hb2);
    m_vb->setStretchFactor(m_hb1,1);
    m_vb->setStretchFactor(m_hb2,10);
    m_ini=new YangContext();
    m_ini->init();
    m_ini->streams.m_playBuffer=new YangSynBuffer();
    //m_ini->rtc.mixAvqueue=0;
    m_player= YangPlayerHandle::createPlayerHandle(m_ini);

    YangSocket su;
    char s[128]={0};
    sprintf(s,"webrtc://%s:1985/live/livestream",su.getLocalInfo().c_str());
    ui->m_url->setText(s);
    localPort=16005;

    yang_setLogLevle(5);
    yang_setLogFile(1);
    m_isStartplay=false;



}

MainWindow::~MainWindow()
{
    delete ui;
    yang_delete(m_videoWin);
    yang_delete(m_player);
    yang_closeLogFile();
    yang_delete(m_ini);

}


void MainWindow::initVideoThread(YangRecordThread *prt){
    m_videoThread=prt;
    m_videoThread->m_video=m_videoWin;
    m_videoThread->initPara();
    m_videoThread->m_syn= m_ini->streams.m_playBuffer;

}

void MainWindow::on_m_b_play_clicked()
{
    if(m_player) {


        //if(m_videoThread&&m_videoThread->m_syn) m_videoThread->m_syn->setInVideoBuffer(m_player->getVideoBuffer());
    }
    if(!m_isStartplay){

        ui->m_b_play->setText("stop");
        if(m_player) m_player->play(ui->m_url->text().toStdString(),localPort);
        m_isStartplay=!m_isStartplay;

        // m_recTimeLen=0;
    }else{
        ui->m_b_play->setText("play");
       if(m_player) m_player->stopPlay();
        // m_rec->stopRecord();
        // yang_post_message(YangM_Rec_Stop,0,NULL);
        // m_timer->stop();
        m_isStartplay=!m_isStartplay;
    }
}

