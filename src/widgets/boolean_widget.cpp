#include "boolean_widget.h"
#include <QHBoxLayout>

BooleanWidget::BooleanWidget(GlobalInfo& globalInfo, const std::string& name): m_globalInfo(globalInfo) {
	setLayout(new QHBoxLayout());
	layout()->setContentsMargins(0, 0, 0, 0);
	nameLabel = new QLabel(QString::fromStdString(name));
	layout()->addWidget(nameLabel);
	checkBox = new QCheckBox();
	layout()->addWidget(checkBox);
	layout()->setAlignment(checkBox, Qt::AlignmentFlag::AlignRight);
	
	connect(checkBox, &QCheckBox::stateChanged, this, &BooleanWidget::onStateChanged);
}

void BooleanWidget::onStateChanged() {
	emit stateChanged(checkBox->isChecked());
}