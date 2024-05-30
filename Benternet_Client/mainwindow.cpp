#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->input_bttn_connect, &QPushButton::clicked, this, &MainWindow::input_connect_clicked);
	connect(ui->translate_bttn, &QPushButton::clicked, this, &MainWindow::input_translate_clicked);
	connect(ui->input_lang_source, &QComboBox::currentIndexChanged, this, &MainWindow::input_lang_source_selected);
}



MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::input_connect_clicked()
{
	username = getUsername();

	if (username.empty()) {
		QMessageBox::warning(this, "Error", "Username can not be empty");
	} else {
		push.connect(ZMQ_SERVER_PUSH_ADRESS);
		sub.connect(ZMQ_SERVER_SUB_ADRESS);

		sub.set(zmq::sockopt::subscribe, ZMQ_SUB_FILTER_1);
		connected = true;
	}
}

void MainWindow::input_translate_clicked()
{

}

void MainWindow::input_lang_source_selected()
{
	std::string source_lang = getSourceLanguage();
	if (source_lang.empty()) {
		QMessageBox::warning(this, "Error", "Select an source language");
	} else if (source_lang != "auto") {
		std::ostringstream oss;
		oss << ZMQ_SUB_FILTER_1 << ">" << username << ">" << "langs" << ">" << source_lang;
		send_msg(oss.str());
	}
}


std::string MainWindow::getUsername()
{
	return ui->input_username->text().toStdString();
}

std::string MainWindow::getSourceLanguage()
{
	return ui->input_lang_source->currentText().toStdString();
}

void MainWindow::setTargetLanguage()
{
	ui->input_lang_target->addItems(lang_list);
}

std::string MainWindow::getTextInput()
{
	return ui->input_text->text().toStdString();
}

void MainWindow::incoming_msg()
{
	while (sub.handle() != NULL) {
		qDebug() << "[+] ZMQ Listening...";
		zmq::recv_result_t result = sub.recv(zmq_msg);
		if (result.has_value()) {
			std::string rx_data = std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
		}
	}
}

void MainWindow::send_msg(std::string msg)
{
	if (push.handle() != NULL) {
		push.send(zmq::buffer(msg), zmq::send_flags::none);
	} else {
		QMessageBox::warning(this, "Error", "Could not push message");
	}
}


