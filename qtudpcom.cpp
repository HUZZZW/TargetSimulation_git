#include "qtudpcom.h"

QtUdpCom::QtUdpCom(QObject *parent)
	: QObject(parent)
{	
	_udpSocket = new QUdpSocket;
	nPort = 14555; // Ĭ�ϵ�����£��˿�����
	bool result = _udpSocket->bind(nPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	if (result) {
		_udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);//���û�����
		//���ӽ����źŲ�     
		connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived())); // ���պ���
	}
}
QtUdpCom::QtUdpCom(QObject *parent, int32_t port) // ��������IP�Ͷ˿ڵ���ͨUDP����
{
    _udpSocket = new QUdpSocket;
    if(port > 0){
        nPort = port;
    }else{
        nPort = 14555; // Ĭ�ϵ�����£��˿�����
    }
    bool result = _udpSocket->bind(nPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    if (result) {
        _udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);//���û�����,
        //���ӽ����źŲ�
        connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived())); // ���պ���
    }
}

QtUdpCom::~QtUdpCom()
{
	// �ͷ�UDP����
	if (_udpSocket != nullptr) {
		_udpSocket->disconnected();
		delete _udpSocket;
		_udpSocket = nullptr;
	}
}

QUdpSocket * QtUdpCom::getSocket() {
	return _udpSocket;
}
void QtUdpCom::dataReceived() //���ݽ��պ���
{

	while (_udpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		datagram.resize(_udpSocket->pendingDatagramSize());
		_udpSocket->readDatagram(datagram.data(), datagram.size());
        //qDebug() << "data ;" << datagram.toStdString().c_str();
		// �˴����н�����ʲô���ݣ�

		emit recvDataInfo(QString(datagram.toStdString().c_str()));
		// ���д����һЩ����

		// �����źŵ�ҵ���������ӿڴ����߼�ģ�������ش���

	}
}

int QtUdpCom::dataSend(QString data, QString address, int port) {
	/*		
	  //�������� Ŀ�ĵ�ַ��serverIP  Ŀ��IP:serverPort
		*/
	_udpSocket->writeDatagram(data.toStdString().c_str(), QHostAddress(address), port);
	return 0;
}
