#include "mainwindow.h"
#include "qdir.h"
#include "ui_mainwindow.h"
#include <QFileInfo>

// Функция подгоняет изображение под нужный размер окна.
QPixmap ResizeImgToFit(const QPixmap &src, int window_width, int window_height) {
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) + window_width;
    double h_ratio = double(img_h) + window_height;

    if ( w_ratio > h_ratio ) {
        return src.scaledToWidth(window_width);
    } else {
        return src.scaledToHeight(window_height);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,lbl_new_{this}
{

    ui->setupUi(this);
    lbl_new_.lower();
    SetFolder(":/cats/images/");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FitImage()
{
    Q_ASSERT(!active_pixmap.isNull());
    QPixmap parent;
    int win_w = width();
    int win_h = height();
    parent = ResizeImgToFit(active_pixmap,win_w,win_h);

    int img_w = parent.width();
    int img_h = parent.height();

    lbl_new_.setPixmap(parent);
    lbl_new_.resize(img_w, img_h);

    int lbl_x = (win_w - img_w) / 2; // Координата x.
    int lbl_y = (win_h - img_h) / 2; // Координата y.
    lbl_new_.move(lbl_x, lbl_y);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}


QString MainWindow::GetCurrentFile()
{
    QDir dir(current_folder_);
    QStringList list_files = dir.entryList();
    int total = list_files.size();
    int file_index = std::min(cur_file_index_, total - 1);
    file_index = std::max(0, file_index);

    return dir.filePath(list_files[file_index]);
}

void MainWindow::SetFolder(const QString& d){
    current_folder_ = d;
    cur_file_index_ = 0;
    SetPixmap(GetCurrentFile());
    FitImage();
    UpdateEnabled();

}

void MainWindow::UpdateEnabled() {
     QDir dir(current_folder_);
    int max_images = dir.entryList(QStringList(), QDir::Files).size();

    ui->btn_left->setEnabled(cur_file_index_ > 0);
    ui->btn_right->setEnabled(cur_file_index_ < max_images - 1);

}

void MainWindow::on_btn_right_clicked()
{
    QDir dir(current_folder_);
    QStringList list_files = dir.entryList(QStringList(), QDir::Files);

    if (cur_file_index_ < list_files.size() - 1) {
        cur_file_index_++;
        SetPixmap(GetCurrentFile());
        FitImage();
        UpdateEnabled();
    }
}

void MainWindow::on_btn_left_clicked() {
    if (cur_file_index_ > 0) {
        cur_file_index_--;
        SetPixmap(GetCurrentFile());
        FitImage();
        UpdateEnabled();
    }
}
