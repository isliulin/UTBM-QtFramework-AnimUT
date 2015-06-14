#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include "ui_AnimUT.h"

#include "Controls.h"

Controls::Controls(Ui::AnimUT* ui)
{
    this->ui = ui;
    layout = ui->ControlsLayout;
    controlButton = NULL;
}

Controls::~Controls()
{
    delete controlButton;
}

/**
 * @brief Controls::addButton Easily add a button in the control list
 * @param name - QString - The text of the button
 * @return QPushButton - A pointer of the button
 */
QPushButton *Controls::addButton(QString name)
{
    QPushButton *pushButton;

    pushButton = new QPushButton(this);
    pushButton->setText(name);
    layout->addWidget(pushButton);

    return pushButton;
}

/**
 * @brief Controls::addDivider Easily add a divider in the control list
 * @return QFrame - A pointer of the divider
 */
QFrame *Controls::addDivider()
{
    QFrame *divider;
    divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFrameShadow(QFrame::Sunken);
    layout->addWidget(divider);

    return divider;
}

/**
 * @brief Controls::addSlider Easily add a slider in the control list
 * @return QSlider - A pointer of the slider
 */
QSlider *Controls::addSlider()
{
    QSlider *slider;
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(slider->sizePolicy().hasHeightForWidth());
    slider->setSizePolicy(sizePolicy);
    layout->addWidget(slider);

    return slider;
}

/**
 * @brief Controls::addLabel Easily add a label in the control list
 * @param name - QString - The text of the label
 * @return QLabel - A pointer of the label
 */
QLabel *Controls::addLabel(QString name)
{
    QLabel *label;
    label = new QLabel(this);
    label->setText(name);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
    label->setSizePolicy(sizePolicy);
    layout->addWidget(label);

    return label;
}

/**
 * @brief Controls::addRadioButton Easily add a radioButton in the control list
 * @param name - QString - The text of the radioButton
 * @return QRadioButton - A pointer of the radioButton
 */
QRadioButton *Controls::addRadioButton(QString name)
{
    QRadioButton *radioButton;
    radioButton = new QRadioButton(this);
    radioButton->setText(name);
    layout->addWidget(radioButton);

    return radioButton;
}

/**
 * @brief Controls::addCheckBox Easily add a checkBox in the control list
 * @param name - QString - The text of the checkBox
 * @return QCheckBox - A pointer of the checkBox
 */
QCheckBox *Controls::addCheckBox(QString name)
{
    QCheckBox *checkBox;
    checkBox = new QCheckBox(this);
    checkBox->setText(name);
    layout->addWidget(checkBox);

    return checkBox;
}

/**
 * @brief Controls::addLineEdit Easily add a lineEdit in the control list
 * @param name - QString - The text of the lineEdit
 * @return QLineEdit - A pointer of the lineEdit
 */
QLineEdit *Controls::addLineEdit()
{
    QLineEdit *lineEdit;
    lineEdit = new QLineEdit(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
    lineEdit->setSizePolicy(sizePolicy);
    layout->addWidget(lineEdit);
    return lineEdit;
}

/**
 * @brief Controls::addProgressBar Easily add a progressBar in the control list
 * @param name - QString - The text of the progressBar
 * @return QProgressBar - A pointer of the progressBar
 */
QProgressBar *Controls::addProgressBar()
{
    QProgressBar *progressBar;
    progressBar = new QProgressBar(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
    progressBar->setSizePolicy(sizePolicy);
    layout->addWidget(progressBar);
    return progressBar;
}

/**
 * @brief Controls::addItem Add a widget in the control list
 * @param name - QWidget - The widget you want to add to the scene
 */
void Controls::addItem(QWidget *widget)
{
    layout->addWidget(widget);
}

/**
 * @brief Controls::addAnimationControl Easily add a full connect button to control animation
 * @param amimate     - Animate - The animation object you want to connect
 * @param myFrameRate -   int   - The number of frames per second in the animation, default: 20 frames/second
 */
void Controls::addAnimationControl(Animate *amimate, int myFrameRate)
{
    controlAnimate = amimate;
    frameRate = myFrameRate;
    controlButton = addButton("Start");
    connect(controlButton, SIGNAL(released()), this, SLOT(animationControl())); // connect different signal to the button
    connect(ui->actionStartStop, SIGNAL(triggered()), this, SLOT(animationControl()));
}

/**
 * @brief Controls::animationControl Method used to control the animation
 */
void Controls::animationControl(){
    if (controlAnimate->isRunning()) {
        controlButton->setText("Start");
        ui->actionStartStop->setText("Start");
        controlAnimate->stop();
    } else {
        controlButton->setText("Stop");
        ui->actionStartStop->setText("Stop");
        controlAnimate->start(frameRate);
    }
}
