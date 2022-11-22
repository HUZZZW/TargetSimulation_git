#pragma once

#include <QObject>
#include <QUdpSocket>
class QtUdpCom : public QObject
{
	Q_OBJECT

public:
	QtUdpCom(QObject *parent);
    QtUdpCom(QObject *parent, int32_t port); // 增加端口设置的普通UDP参数
	~QtUdpCom();
private:
	QUdpSocket *_udpSocket;//
	int nType; // UDP类型，0：udp 1：udp组播 2： udp广播
	int nPort; // 绑定端口
public:
	QUdpSocket * getSocket();
signals:
	void recvDataInfo(QString str);

private slots:
	void dataReceived(); //数据接收函数
public:
	int dataSend(QString data, QString address, int port); // 普通UDP客户端发送数据函数
};
