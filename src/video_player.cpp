
#include "video_player.h"

#include <QtWidgets>
#include <QVideoWidget>

VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent)
{
  m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
  QVideoWidget *videoWidget = new QVideoWidget();

  QAbstractButton *openButton = new QPushButton(tr("Open file..."));
  connect(openButton, &QAbstractButton::clicked, this, &VideoPlayer::openFile);

  m_playButton = new QPushButton();
  m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
  m_playButton->setEnabled(false);

  connect(m_playButton, &QAbstractButton::clicked, this, &VideoPlayer::play);

  m_positionSlider = new QSlider(Qt::Horizontal);
  m_positionSlider->setRange(0, 0);

  connect(m_positionSlider, &QAbstractSlider::sliderMoved, this, &VideoPlayer::setPosition);

  m_errorLabel = new QLabel();
  m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

  QBoxLayout *controlLayout = new QHBoxLayout;
  controlLayout->setContentsMargins(0, 0, 0, 0);
  controlLayout->addWidget(m_playButton);
  controlLayout->addWidget(openButton);
  controlLayout->addWidget(m_positionSlider);

  QVBoxLayout *masterLayout = new QVBoxLayout;
  masterLayout->addWidget(videoWidget);
  masterLayout->addWidget(m_errorLabel);
  masterLayout->addLayout(controlLayout);

  setLayout(masterLayout);

  m_mediaPlayer->setVideoOutput(videoWidget);
  connect(m_mediaPlayer, &QMediaPlayer::stateChanged, this, &VideoPlayer::mediaStateChanged);
  connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);
  connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
  connect(m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &VideoPlayer::handleError);
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::openFile()
{
  QFileDialog fileDialog; // TODO
  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog.setWindowTitle("Open video file");
  QStringList supportedMimeTypes = m_mediaPlayer->supportedMimeTypes();
  if (!supportedMimeTypes.isEmpty())
  {
    fileDialog.setMimeTypeFilters(supportedMimeTypes);
  }
  fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
  if (fileDialog.exec() == QDialog::Accepted)
  {
    setUrl(fileDialog.selectedUrls().constFirst());
  }
}

void VideoPlayer::setUrl(const QUrl &url)
{
  m_errorLabel->setText(QString());
  setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
  m_mediaPlayer->setMedia(url);
  m_playButton->setEnabled(true);
}

void VideoPlayer::play()
{
  switch (m_mediaPlayer->state())
  {
  case QMediaPlayer::PlayingState:
    m_mediaPlayer->pause();
    break;

  default:
    m_mediaPlayer->play();
    break;
  }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
  if (state == QMediaPlayer::PlayingState)
  {
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    return;
  }
  m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
  return;
}

void VideoPlayer::positionChanged(qint64 position)
{
  m_positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
  m_positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
  m_mediaPlayer->setPosition(position);
}

void VideoPlayer::handleError()
{
  m_playButton->setEnabled(false);
  const QString errorString = m_mediaPlayer->errorString();
  QString message = "Error: ";
  if (errorString.isEmpty())
    message += " #" + QString::number(int(m_mediaPlayer->error()));
  else
    message += errorString;
  m_errorLabel->setText(message);
}