/********************************************************************************
** Form generated from reading UI file 'ReceiveFrame.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEFRAME_H
#define UI_RECEIVEFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include "Gui/Common/QRLabel.h"
#include "Gui/Common/WalletBlueButton.h"
#include "Gui/Common/WalletLinkLikeButton.h"
#include "Gui/Common/WalletTextLabel.h"

QT_BEGIN_NAMESPACE

class Ui_ReceiveFrame
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *m_createRequestFrame;
    QGridLayout *gridLayout;
    QDoubleSpinBox *m_amountRequestSpinBox;
    QSpacerItem *horizontalSpacer_2;
    WalletGui::WalletNormalGrayTextLabel *amountLabel;
    WalletGui::WalletNormalGrayTextLabel *paymentIdLabel;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *m_paymentIdRequestEdit;
    WalletGui::WalletNormalLinkLikeButton *m_generateIdButton;
    WalletGui::WalletNormalGrayTextLabel *labelLabel;
    QLineEdit *m_labelEdit;
    QSpacerItem *horizontalSpacer_3;
    WalletGui::WalletHeaderLabel *label;
    QHBoxLayout *horizontalLayout_2;
    WalletGui::WalletHeaderLabel *label_2;
    QFrame *m_showRequestFrame;
    QHBoxLayout *horizontalLayout;
    WalletGui::QRLabel *m_qrCodeRequestLabel;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *m_requestTextEdit;
    QSpacerItem *verticalSpacer;
    QFrame *m_receiveFrameButtons;
    QHBoxLayout *m_receiveFrameButtonsLayout;
    QSpacerItem *horizontalSpacer;
    WalletGui::WalletNormalBlueButton *m_copyToClipBoardButton;
    WalletGui::WalletNormalBlueButton *m_saveRequestButton;
    WalletGui::WalletNormalBlueButton *m_saveQrCodeButton;

    void setupUi(QFrame *ReceiveFrame)
    {
        if (ReceiveFrame->objectName().isEmpty())
            ReceiveFrame->setObjectName(QStringLiteral("ReceiveFrame"));
        ReceiveFrame->resize(950, 627);
        ReceiveFrame->setFrameShape(QFrame::NoFrame);
        ReceiveFrame->setFrameShadow(QFrame::Plain);
        verticalLayout = new QVBoxLayout(ReceiveFrame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        m_createRequestFrame = new QFrame(ReceiveFrame);
        m_createRequestFrame->setObjectName(QStringLiteral("m_createRequestFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_createRequestFrame->sizePolicy().hasHeightForWidth());
        m_createRequestFrame->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        m_createRequestFrame->setFont(font);
        gridLayout = new QGridLayout(m_createRequestFrame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(18, 9, 18, 9);
        m_amountRequestSpinBox = new QDoubleSpinBox(m_createRequestFrame);
        m_amountRequestSpinBox->setObjectName(QStringLiteral("m_amountRequestSpinBox"));
        m_amountRequestSpinBox->setDecimals(12);
        m_amountRequestSpinBox->setMaximum(1e+09);

        gridLayout->addWidget(m_amountRequestSpinBox, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(299, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 2);

        amountLabel = new WalletGui::WalletNormalGrayTextLabel(m_createRequestFrame);
        amountLabel->setObjectName(QStringLiteral("amountLabel"));

        gridLayout->addWidget(amountLabel, 1, 0, 1, 1);

        paymentIdLabel = new WalletGui::WalletNormalGrayTextLabel(m_createRequestFrame);
        paymentIdLabel->setObjectName(QStringLiteral("paymentIdLabel"));

        gridLayout->addWidget(paymentIdLabel, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_paymentIdRequestEdit = new QLineEdit(m_createRequestFrame);
        m_paymentIdRequestEdit->setObjectName(QStringLiteral("m_paymentIdRequestEdit"));

        horizontalLayout_3->addWidget(m_paymentIdRequestEdit);

        m_generateIdButton = new WalletGui::WalletNormalLinkLikeButton(m_createRequestFrame);
        m_generateIdButton->setObjectName(QStringLiteral("m_generateIdButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_generateIdButton->sizePolicy().hasHeightForWidth());
        m_generateIdButton->setSizePolicy(sizePolicy1);
        m_generateIdButton->setMinimumSize(QSize(80, 0));
        m_generateIdButton->setFlat(true);

        horizontalLayout_3->addWidget(m_generateIdButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 3);

        labelLabel = new WalletGui::WalletNormalGrayTextLabel(m_createRequestFrame);
        labelLabel->setObjectName(QStringLiteral("labelLabel"));

        gridLayout->addWidget(labelLabel, 3, 0, 1, 1);

        m_labelEdit = new QLineEdit(m_createRequestFrame);
        m_labelEdit->setObjectName(QStringLiteral("m_labelEdit"));
        m_labelEdit->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(m_labelEdit, 3, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 3, 1, 1);

        label = new WalletGui::WalletHeaderLabel(m_createRequestFrame);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 30));
        label->setMargin(0);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(m_createRequestFrame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(18, -1, 18, -1);
        label_2 = new WalletGui::WalletHeaderLabel(ReceiveFrame);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setMargin(0);

        horizontalLayout_2->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_2);

        m_showRequestFrame = new QFrame(ReceiveFrame);
        m_showRequestFrame->setObjectName(QStringLiteral("m_showRequestFrame"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_showRequestFrame->sizePolicy().hasHeightForWidth());
        m_showRequestFrame->setSizePolicy(sizePolicy2);
        m_showRequestFrame->setMinimumSize(QSize(600, 350));
        horizontalLayout = new QHBoxLayout(m_showRequestFrame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(18, -1, 18, -1);
        m_qrCodeRequestLabel = new WalletGui::QRLabel(m_showRequestFrame);
        m_qrCodeRequestLabel->setObjectName(QStringLiteral("m_qrCodeRequestLabel"));
        m_qrCodeRequestLabel->setMinimumSize(QSize(300, 300));

        horizontalLayout->addWidget(m_qrCodeRequestLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_requestTextEdit = new QTextEdit(m_showRequestFrame);
        m_requestTextEdit->setObjectName(QStringLiteral("m_requestTextEdit"));

        verticalLayout_2->addWidget(m_requestTextEdit);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addWidget(m_showRequestFrame);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_receiveFrameButtons = new QFrame(ReceiveFrame);
        m_receiveFrameButtons->setObjectName(QStringLiteral("m_receiveFrameButtons"));
        m_receiveFrameButtonsLayout = new QHBoxLayout(m_receiveFrameButtons);
        m_receiveFrameButtonsLayout->setObjectName(QStringLiteral("m_receiveFrameButtonsLayout"));
        m_receiveFrameButtonsLayout->setContentsMargins(18, 18, 18, 18);
        horizontalSpacer = new QSpacerItem(500, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_receiveFrameButtonsLayout->addItem(horizontalSpacer);

        m_copyToClipBoardButton = new WalletGui::WalletNormalBlueButton(m_receiveFrameButtons);
        m_copyToClipBoardButton->setObjectName(QStringLiteral("m_copyToClipBoardButton"));
        sizePolicy1.setHeightForWidth(m_copyToClipBoardButton->sizePolicy().hasHeightForWidth());
        m_copyToClipBoardButton->setSizePolicy(sizePolicy1);
        m_copyToClipBoardButton->setMinimumSize(QSize(150, 0));
        m_copyToClipBoardButton->setBaseSize(QSize(150, 0));
        m_copyToClipBoardButton->setFlat(true);

        m_receiveFrameButtonsLayout->addWidget(m_copyToClipBoardButton);

        m_saveRequestButton = new WalletGui::WalletNormalBlueButton(m_receiveFrameButtons);
        m_saveRequestButton->setObjectName(QStringLiteral("m_saveRequestButton"));
        sizePolicy1.setHeightForWidth(m_saveRequestButton->sizePolicy().hasHeightForWidth());
        m_saveRequestButton->setSizePolicy(sizePolicy1);
        m_saveRequestButton->setMinimumSize(QSize(150, 0));
        m_saveRequestButton->setBaseSize(QSize(150, 0));
        m_saveRequestButton->setFlat(true);

        m_receiveFrameButtonsLayout->addWidget(m_saveRequestButton);

        m_saveQrCodeButton = new WalletGui::WalletNormalBlueButton(m_receiveFrameButtons);
        m_saveQrCodeButton->setObjectName(QStringLiteral("m_saveQrCodeButton"));
        sizePolicy1.setHeightForWidth(m_saveQrCodeButton->sizePolicy().hasHeightForWidth());
        m_saveQrCodeButton->setSizePolicy(sizePolicy1);
        m_saveQrCodeButton->setMinimumSize(QSize(150, 0));
        m_saveQrCodeButton->setBaseSize(QSize(150, 0));
        m_saveQrCodeButton->setFlat(true);

        m_receiveFrameButtonsLayout->addWidget(m_saveQrCodeButton);


        verticalLayout->addWidget(m_receiveFrameButtons);

        QWidget::setTabOrder(m_amountRequestSpinBox, m_paymentIdRequestEdit);
        QWidget::setTabOrder(m_paymentIdRequestEdit, m_labelEdit);
        QWidget::setTabOrder(m_labelEdit, m_generateIdButton);
        QWidget::setTabOrder(m_generateIdButton, m_requestTextEdit);
        QWidget::setTabOrder(m_requestTextEdit, m_copyToClipBoardButton);
        QWidget::setTabOrder(m_copyToClipBoardButton, m_saveRequestButton);
        QWidget::setTabOrder(m_saveRequestButton, m_saveQrCodeButton);

        retranslateUi(ReceiveFrame);
        QObject::connect(m_amountRequestSpinBox, SIGNAL(editingFinished()), ReceiveFrame, SLOT(generateRequest()));
        QObject::connect(m_paymentIdRequestEdit, SIGNAL(editingFinished()), ReceiveFrame, SLOT(generateRequest()));
        QObject::connect(m_labelEdit, SIGNAL(editingFinished()), ReceiveFrame, SLOT(generateRequest()));
        QObject::connect(m_saveQrCodeButton, SIGNAL(clicked()), ReceiveFrame, SLOT(saveQrCode()));
        QObject::connect(m_saveRequestButton, SIGNAL(clicked()), ReceiveFrame, SLOT(saveRequest()));
        QObject::connect(m_copyToClipBoardButton, SIGNAL(clicked()), ReceiveFrame, SLOT(copyRequest()));
        QObject::connect(m_generateIdButton, SIGNAL(clicked()), ReceiveFrame, SLOT(generatePaymentIdClicked()));

        QMetaObject::connectSlotsByName(ReceiveFrame);
    } // setupUi

    void retranslateUi(QFrame *ReceiveFrame)
    {
        ReceiveFrame->setWindowTitle(QApplication::translate("ReceiveFrame", "Frame", 0));
        amountLabel->setText(QApplication::translate("ReceiveFrame", "AMOUNT", 0));
        paymentIdLabel->setText(QApplication::translate("ReceiveFrame", "PAYMENT ID", 0));
        m_generateIdButton->setText(QApplication::translate("ReceiveFrame", "Generate", 0));
        labelLabel->setText(QApplication::translate("ReceiveFrame", "LABEL", 0));
        label->setText(QApplication::translate("ReceiveFrame", "Create request", 0));
        label_2->setText(QApplication::translate("ReceiveFrame", "Payment Request", 0));
        m_qrCodeRequestLabel->setText(QString());
        m_copyToClipBoardButton->setText(QApplication::translate("ReceiveFrame", "Copy to clipboard", 0));
        m_saveRequestButton->setText(QApplication::translate("ReceiveFrame", "Save Request", 0));
        m_saveQrCodeButton->setText(QApplication::translate("ReceiveFrame", "Save QR Code", 0));
    } // retranslateUi

};

namespace Ui {
    class ReceiveFrame: public Ui_ReceiveFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEFRAME_H
