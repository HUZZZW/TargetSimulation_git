#pragma once

#include <QObject>
#include <QUdpSocket>
class QtUdpCom : public QObject
{
	Q_OBJECT

public:
	QtUdpCom(QObject *parent);
    QtUdpCom(QObject *parent, int32_t port); // ���Ӷ˿����õ���ͨUDP����
	~QtUdpCom();
private:
	QUdpSocket *_udpSocket;//
	int nType; // UDP���ͣ�0��udp 1��udp�鲥 2�� udp�㲥
	int nPort; // �󶨶˿�
public:
	QUdpSocket * getSocket();
signals:
	void recvDataInfo(QString str);

private slots:
	void dataReceived(); //���ݽ��պ���
public:
	int dataSend(QString data, QString address, int port); // ��ͨUDP�ͻ��˷������ݺ���
};
