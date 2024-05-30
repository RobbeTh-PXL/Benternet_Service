#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow), ctx(1), sub(ctx, ZMQ_SUB), push(ctx, ZMQ_PUSH)
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


		std::ostringstream oss;
		oss << ZMQ_PUSH_FILTER_1 << ">" << username;
		sub.set(zmq::sockopt::subscribe, oss.str());
		connected = true;
	}
}

void MainWindow::input_translate_clicked()
{
	if (connected && !source_lang.empty()) {
		target_lang = getTargetLanguage();
		std::string text = getTextInput();
		if (target_lang.empty() || text.empty()) {
			QMessageBox::warning(this, "Error", "Select an target language, and text");
		} else {
			request_translate = true;
			std::ostringstream oss;
			oss << ZMQ_SUB_FILTER_1 << ">" << username << ">" << source_lang << "-" << target_lang << ">" << text;
			send_msg(oss.str());
		}
	}
}

void MainWindow::input_lang_source_selected()
{
	if (connected) {
		source_lang = getSourceLanguage();
		if (source_lang.empty()) {
			QMessageBox::warning(this, "Error", "Select an source language");
		} else if (source_lang != "auto") {
			std::ostringstream oss;
			oss << ZMQ_SUB_FILTER_1 << ">" << username << ">" << "langs" << ">" << source_lang;
			request_langs = true;
			send_msg(oss.str());
		} else if (source_lang == "auto") {
			std::ostringstream oss;
			oss << ZMQ_SUB_FILTER_1 << ">" << username << ">" << "langs" << ">" << "en";
			request_langs = true;
			send_msg(oss.str());
		}
	} else {
		QMessageBox::warning(this, "Error", "Connect Client first");
		ui->input_lang_source->setCurrentIndex(0);
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

std::string MainWindow::getTargetLanguage()
{
	return ui->input_lang_target->currentText().toStdString();
}

std::string MainWindow::getTextInput()
{
	return ui->input_text->text().toStdString();
}

void MainWindow::incoming_msg()
{
	qDebug() << "[+] ZMQ Listening...";
	while (sub.handle() != NULL) {
		zmq::recv_result_t result = sub.recv(zmq_msg);
		if (result.has_value()) {
			std::string rx_data = std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
			qDebug() << rx_data;

			// Remove the prefix "translate!>test>" if present
			std::ostringstream oss;
			oss << ZMQ_PUSH_FILTER_1 ">" << username << ">";
			std::string prefix = oss.str();
			if (rx_data.find(prefix) == 0) {
				rx_data = rx_data.substr(prefix.length());
			}

			if (request_langs) {
				ui->output_log->addItem(QString::fromStdString(rx_data));
				ui->output_log->scrollToBottom();
				qDebug() << "[+] Request Lang";

				// Remove the trailing comma if present
				if (!rx_data.empty() && rx_data.back() == ',') {
					rx_data.pop_back(); // Remove the last character
				}

				// Split the string by comma
				std::vector<std::string> qlist;
				std::stringstream ss(rx_data);
				std::string item;

				while (std::getline(ss, item, ',')) {
					qlist.push_back(item);
				}

				for (const std::string &str : qlist) {
					lang_list.append(QString::fromStdString(str));
				}

				lang_list.removeLast();

				ui->input_lang_target->clear();
				ui->input_lang_target->addItems(lang_list);
				ui->input_lang_target->update();

				qDebug() << "[+] List size" << lang_list.size();

				request_langs = false;
			} else if (request_translate) {
				qDebug() << rx_data;
				ui->input_text->clear();
				ui->output_com->addItem(QString::fromStdString(rx_data));
				ui->output_com->scrollToBottom();
				request_translate = false;
			}
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


