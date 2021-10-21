#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <Socket/Server.hpp>
#include <Socket/SocketOptionsBuilder.hpp>

#include "mainwindow.h"

int main(int argc, char *argv[]) {

	// Initialize Winsock
	WSADATA wsaData;
	int iResult;
	u_long iMode = 0;

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");

	auto builder = (new SocketOptionBuilder())
		->UsingUDP()
		->WithMaxQueuedConnection(8)
		->WithReuseAddress()
		->WithReusePort()
		->WithSSL(false)
		->WithServerPort(8080)
		->Build();

	auto server = Server::makeShared(builder);

	server->OnClientConnected([](SocketContext* ctx) -> void {

	});
	server->OnClientDisconnected([](SocketContext* ctx) -> void {

	});
	server->OnMessage([](SocketContext* ctx, std::string& message) -> void {

	});
	server->SetEventManager(new EventManager());
	server->Setup();
	server->Boot();

	//Q_INIT_RESOURCE(application);

	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("QtProject");
	QCoreApplication::setApplicationName("Application Example");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);
	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::applicationName());
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The file to open.");
	parser.process(app);

	MainWindow mainWin;
	if (!parser.positionalArguments().isEmpty())
		mainWin.loadFile(parser.positionalArguments().first());
	mainWin.show();

	return app.exec();
}
