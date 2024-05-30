#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zmq.hpp>

#define ZMQ_SERVER_PUSH_ADRESS "tcp://localhost:24041"
#define ZMQ_SERVER_SUB_ADRESS "tcp://localhost:24042"

#define ZMQ_SUB_FILTER_1 "translate?"
#define ZMQ_PUSH_FILTER_1 "translate!"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void input_connect_clicked();
	void input_translate_clicked();
	void input_lang_source_selected();

private:
	Ui::MainWindow *ui;

	std::string getUsername();
	std::string getSourceLanguage();
	void setTargetLanguage();
	std::string getTextInput();

	std::string username;
	bool connected = false;
	QList<QString> lang_list;

	zmq::context_t ctx;
	zmq::socket_t sub;
	zmq::socket_t push;
	zmq::message_t zmq_msg;

	void incoming_msg();
	void send_msg(std::string msg);
};
#endif // MAINWINDOW_H
