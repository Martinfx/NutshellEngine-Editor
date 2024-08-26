#pragma once
#include "../common/global_info.h"
#include <QMenu>
#include <QAction>

class ProjectMenu : public QMenu {
	Q_OBJECT
public:
	ProjectMenu(GlobalInfo& globalInfo);

private:
	void openProjectSettings();
	void updateBaseProject();

private:
	GlobalInfo& m_globalInfo;

	QAction* m_openProjectSettingsAction;
	QAction* m_updateBaseProject;
};