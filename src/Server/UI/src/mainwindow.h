//
// Created by Nuno Silva on 07/10/2021.
//

#ifndef HELLOWORLD__MAINWINDOW_H_
#define HELLOWORLD__MAINWINDOW_H_

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QSessionManager>

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

  void loadFile(const QString &fileName);

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void newFile();
  void open();
  bool save();
  bool saveAs();
  void about();
  void documentWasModified();
#ifndef QT_NO_SESSIONMANAGER
  void commitData(QSessionManager &);
#endif

 private:
  void createActions();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool maybeSave();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  QPlainTextEdit *textEdit;
  QString curFile;
};

#endif //HELLOWORLD__MAINWINDOW_H_
