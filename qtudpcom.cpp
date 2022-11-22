#include "qtudpcom.h"

QtUdpCom::QtUdpCom(QObject *parent)
	: QObject(parent)
{	
	_udpSocket = new QUdpSocket;
	nPort = 14555; // 默认的情况下，端口设置
	bool result = _udpSocket->bind(nPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	if (result) {
		_udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);//设置缓冲区
		//连接接收信号槽     
		connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived())); // 接收函数
	}
}
QtUdpCom::QtUdpCom(QObject *parent, int32_t port) // 增加设置IP和端口的普通UDP参数
{
    _udpSocket = new QUdpSocket;
    if(port > 0){
        nPort = port;
    }else{
        nPort = 14555; // 默认的情况下，端口设置
    }
    bool result = _udpSocket->bind(nPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    if (result) {
        _udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);//设置缓冲区,
        //连接接收信号槽
        connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived())); // 接收函数
    }
}

QtUdpCom::~QtUdpCom()
{
	// 释放UDP对象
	if (_udpSocket != nullptr) {
		_udpSocket->disconnected();
		delete _udpSocket;
		_udpSocket = nullptr;
	}
}

QUdpSocket * QtUdpCom::getSocket() {
	return _udpSocket;
}
void QtUdpCom::dataReceived() //数据接收函数
{

	while (_udpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		datagram.resize(_udpSocket->pendingDatagramSize());
		_udpSocket->readDatagram(datagram.data(), datagram.size());
        //qDebug() << "data ;" << datagram.toStdString().c_str();
		// 此处进行解析是什么数据？

		emit recvDataInfo(QString(datagram.toStdString().c_str()));
		// 进行处理的一些操作

		// 发送信号到业务或者网络接口处理逻辑模块进行相关处理

	}
}

int QtUdpCom::dataSend(QString data, QString address, int port) {
	/*		
	  //发送数据 目的地址：serverIP  目的IP:serverPort
		*/
	_udpSocket->writeDatagram(data.toStdString().c_str(), QHostAddress(address), port);
	return 0;
}
