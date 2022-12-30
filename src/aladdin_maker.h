#ifndef ALADDIN_MAKER_H
#define ALADDIN_MAKER_H

#include <QObject>
#include <QColor>
#include <QNetworkConfigurationManager>
#include <QHostInfo>

class AladdinMaker : public QObject
{
    Q_OBJECT
    Q_ENUMS(GenerateAlgorithm)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor timeColor READ timeColor)
    Q_PROPERTY(int fullTime READ fullTime WRITE setFullTime)

public:
    AladdinMaker(QObject *parent = 0);
    ~AladdinMaker();

    enum GenerateAlgorithm{
        RandomRGB,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };

    QColor color() const;
    void setColor(const QColor & color);
    QColor timeColor() const;
    int fullTime() const;

    Q_INVOKABLE void setFullTime(const int & fullTime);
    Q_INVOKABLE GenerateAlgorithm algorithm() const;
    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

signals:
    void colorChanged(const QColor & color);
    void currentTime(const QString &strTime);
    void stopStudyStatus();
    void actualTime(const int &intTime);
    void currNetStat(bool isOnline);

public slots:
    void start();
    void stop();
    void onLookupHost(QHostInfo host);
    void setNetworkStatus(bool isOnline);

protected:
    void timerEvent(QTimerEvent *e);

private:
    GenerateAlgorithm m_algorithm;
    QColor m_currentColor;
    int m_nTimer;
    int m_full_time{10};
    int m_target_time;
    int m_actual_time;

    QNetworkConfigurationManager *ncm;
    void check_net_online();
};

#endif // COLORMAKER_H

