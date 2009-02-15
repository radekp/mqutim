/*
    SeparateChatWindow

    Copyright (c) 2008 by Rustam Chakin <qutim.develop@gmail.com>

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*/

#ifndef SEPARATECHATWINDOW_H
#define SEPARATECHATWINDOW_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QTextEdit>
#include <QTextBrowser>
#include <QLabel>
#include <QMenu>
#include <QWidgetAction>
#include <QSplitter>
#include "../abstractchatlayer.h"
#include "chatwindowstyleoutput.h"
#include "../pluginsystem.h"
#include "chatemoticonmenu.h"
#include <QTextCursor>
#include "ui_chatwindowform.h"

class SeparateChatWindow : public QWidget
{
    Q_OBJECT

public:
    SeparateChatWindow(const QString &protocol_name,
    		const QString &account_name,
    		const QString &item_name,
    		QWidget *parent = 0);
    ~SeparateChatWindow();
    
    static bool lengthLessThan (const QString &s1, const QString &s2);
    void addMessage(const QString &message, bool in
    		, const QString &message_date, bool history);
    void addServiceMessage(const QString &message);
    void setOptions(bool remove_after, quint16 remove_count,
    		bool close_after, bool show_names, bool on_enter,
    		bool typing_notifications);
    void contactTyping(bool typing);
    void messageDelievered(int position);
    void windowActivatedByUser();
    QString getProtocolName()
    {
    	return m_protocol_name;
    }
    QString getAccountName()
    {
    	return m_account_name;
    }
    QString getItemName()
    {
    	return m_item_name;
    }
	void setContactClientIcon();
	void addSeparator();
	int getCursorPosition();
  void setID(const QString &id);

protected:
	bool event(QEvent *event);  

private slots:
	void on_sendButton_clicked();
	void on_chatInputEdit_textChanged();
	void typingNow();
	void clearChat();
  void showHistory();
	void on_quoteButton_clicked();
	void windowFocused();
	void onCustomContextMenuRequested(const QPoint & pos);
	void newsOnLinkClicked(const QUrl &url);

private:
	Ui::ChatWindow ui;
	void setIconsToButtons();
	QString invertMessage(QString &message);
	void moveCursorToEnd();
  void checkForActiveState();
  void updateInfo();
  
	AbstractChatLayer &m_abstract_chat_layer;
  
	QString m_protocol_name;
	QString m_account_name;
	QString m_item_name;
	QString m_client_id;
  
  QString m_contact_name;
  QString m_own_name;
  
	QPushButton *m_send_button;
	QTextEdit *m_plain_text_edit;
	QTextBrowser *m_text_browser;
  
  bool m_last_message_sender;
  bool m_lock_for_first_message;
  PluginSystem &m_plugin_system;
  
  QHash<QString, QString> m_urls;
  QString m_now_html;
  bool m_remove_message_after;
  quint16 m_remove_count;
  QList<quint64> m_message_positions;
  quint32 m_webkit_header_offset;
  bool m_close_after_send;
  bool m_show_names;
  bool m_send_typing_notifications;
  bool m_text_changed;
  bool m_typing_changed;
  QHash<int,int> m_message_position_offset;
  int m_last_message_icon_position;
  int m_last_message_position;
  bool m_waiting_for_activation;
  QString m_emoticons_path;
  bool m_scroll_at_max;
  quint64 m_current_scroll_position;
  bool m_last_history;
};

#endif // SEPARATECHATWINDOW_H
