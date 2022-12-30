#include <QTimerEvent>
#include <QDateTime>
#include <QDebug>
#include <cstdlib>
#include "aladdin_maker.h"

AladdinMaker::AladdinMaker(QObject *parent)
    : QObject(parent)
    , m_algorithm(RandomRGB)
    , m_currentColor(Qt::black)
    , m_nTimer(0)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    // wifi info refresh module
    qDebug() << "test network!";
    check_net_online();  // get the initial status of network
    ncm = new QNetworkConfigurationManager();
    connect(ncm, SIGNAL(onlineStateChanged(bool)), \
		    this, SLOT(setNetworkStatus(bool)));
}

AladdinMaker::~AladdinMaker()
{
    if (!ncm) {
        delete ncm;
    }
}

QColor AladdinMaker::color() const
{
    return m_currentColor;
}

void AladdinMaker::setColor(const QColor &color)
{
    m_currentColor = color;
    emit colorChanged(m_currentColor);
}

QColor AladdinMaker::timeColor() const
{
    QTime time = QTime::currentTime();
    int r = time.hour();
    int g = time.minute()*2;
    int b = time.second()*4;
    return QColor::fromRgb(r, g, b);
}

int AladdinMaker::fullTime() const
{
    return m_full_time;
}

void AladdinMaker::setFullTime(const int & fullTime)
{
    m_full_time = fullTime * 60;
    m_target_time = m_full_time;
    m_nTimer = startTimer(1000);
}

AladdinMaker::GenerateAlgorithm AladdinMaker::algorithm() const
{
    return m_algorithm;
}

void AladdinMaker::setAlgorithm(GenerateAlgorithm algorithm)
{
    m_algorithm = algorithm;
}

void AladdinMaker::start()
{
    if(m_nTimer == 0)
    {
        system("systemctl restart offline-sss");
	// system("ssh toybrick@192.168.180.8 \"sudo systemctl start study-status.service\"");
    }
}

void AladdinMaker::stop()
{
    if(m_nTimer > 0)
    {
        system("systemctl stop offline-sss");
	//system("ssh toybrick@192.168.180.8 \"sudo bash /home/toybrick/1808_sss/stop_sss.sh\"");

        qDebug() << "exit with sender & aladdin_maker closed!";
        killTimer(m_nTimer);
        m_nTimer = 0;

        QString end_str = "学习提前结束!这不好!";
        emit currentTime(end_str);
        // m_actual_time = (m_target_time - m_full_time) / 60;
        m_actual_time = m_target_time - m_full_time;
        emit actualTime(m_actual_time);
    }
}

void AladdinMaker::check_net_online() {
    QHostInfo::lookupHost("www.baidu.com", this, SLOT(onLookupHost(QHostInfo)));
}

void AladdinMaker::onLookupHost(QHostInfo host) {
    qDebug() << "mgr.isOnline = " << ncm->isOnline();
    if (host.error() == QHostInfo::NoError) {
        qDebug() << "Lookup net status sucessfully! ";
	setNetworkStatus(true);
    } else {
        qDebug() << "Lookup net status failed: " << host.errorString();
        //网络未连接，发送信号通知
	setNetworkStatus(false);
    }
}

void AladdinMaker::setNetworkStatus(bool isOnline) {
    emit currNetStat(isOnline);
}

void AladdinMaker::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_nTimer)
    {
        m_full_time--;
        int left_min = m_full_time / 60;
        int left_sec = m_full_time % 60;
        QString left_min_str;
        QString left_sec_str;
        if (left_min < 10) {
            left_min_str = "0" + QString::number(left_min);
        } else {
            left_min_str = QString::number(left_min);
        }
        if (left_sec < 10) {
            left_sec_str = "0" + QString::number(left_sec);
        } else {
            left_sec_str = QString::number(left_sec);
        }
        QString left_time = left_min_str + " : " + left_sec_str;
        emit currentTime(left_time);

        if(m_full_time < 0)
        {
            killTimer(m_nTimer);
            m_nTimer = 0;
            // m_full_time = 100;
            QString end_str = "学习结束！你真棒！";
            emit currentTime(end_str);
            // m_actual_time = (m_target_time - m_full_time) / 60;
            m_actual_time = m_target_time - m_full_time;
            emit actualTime(m_actual_time);

            emit stopStudyStatus();

            qDebug() << "学习时间到!关闭推流!关闭客户端主控程序!";
        }
    }
    else
    {
        QObject::timerEvent(e);
    }
}

