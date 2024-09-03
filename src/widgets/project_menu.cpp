#include "project_menu.h"
#include "main_window.h"
#include "project_ntpj_file_widget.h"
#include <fstream>

ProjectMenu::ProjectMenu(GlobalInfo& globalInfo) : QMenu("&Project"), m_globalInfo(globalInfo) {
	m_buildAction = addAction("Build and Run", this, &ProjectMenu::launchBuild);
	m_buildAction->setShortcut(QKeySequence::fromString("F5"));
	addSeparator();
	m_openProjectSettingsAction = addAction("Open Project Settings", this, &ProjectMenu::openProjectSettings);
	m_openProjectSettingsAction->setShortcut(QKeySequence::fromString("Ctrl+Shift+P"));
	addSeparator();
	m_importGlobalResources = addAction("Import global resources", this, &ProjectMenu::importGlobalResources);
	m_updateBaseProject = addAction("Update base project", this, &ProjectMenu::updateBaseProject);
}

void ProjectMenu::launchBuild() {
	m_globalInfo.mainWindow->buildBar->launchBuild();
}

void ProjectMenu::openProjectSettings() {
	ProjectNtpjFileWidget* projectNtpjFileWidget = new ProjectNtpjFileWidget(m_globalInfo);
	projectNtpjFileWidget->show();
}

void ProjectMenu::importGlobalResources() {
	std::filesystem::copy("assets/global_resources", m_globalInfo.projectDirectory, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);

	std::fstream optionsFile(m_globalInfo.projectDirectory + "/assets/options/options.ntop", std::ios::in);
	if (optionsFile.is_open()) {
		if (!nlohmann::json::accept(optionsFile)) {
			return;
		}
	}
	else {
		return;
	}

	optionsFile = std::fstream(m_globalInfo.projectDirectory + "/assets/options/options.ntop", std::ios::in);
	nlohmann::json j = nlohmann::json::parse(optionsFile);

	optionsFile = std::fstream(m_globalInfo.projectDirectory + "/assets/options/options.ntop", std::ios::out | std::ios::trunc);
	if (optionsFile.is_open()) {
		if (!j.contains("firstScenePath")) {
			j["firstScenePath"] = "assets/scenes/default_scene.ntsn";
		}
		optionsFile << j.dump(1, '\t');
	}
}

void ProjectMenu::updateBaseProject() {
	std::filesystem::copy("assets/base_project", m_globalInfo.projectDirectory, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
}
