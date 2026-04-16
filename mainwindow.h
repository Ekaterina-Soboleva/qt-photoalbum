#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>

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

    void SetPixmap(const QString path) {
        active_pixmap = QPixmap(path);
    }

    void FitImage();
    void SetFolder(const QString& d);
    QString GetCurrentFile();
    void UpdateEnabled();

private slots:
    void on_btn_right_clicked();

    void on_btn_left_clicked();

private:
    void resizeEvent(QResizeEvent *event) override;


private:
    Ui::MainWindow *ui;
    QPixmap active_pixmap;
    QLabel lbl_new_;
    QString current_folder_;
     int cur_file_index_ = 0;
};
#endif // MAINWINDOW_H
