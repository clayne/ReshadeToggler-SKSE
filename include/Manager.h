#pragma once

struct MenuToggleInformation
{
	std::string effectName{};
	std::string menuName{};
	bool state = true;
};

struct WeatherToggleInformation
{
	std::string effectName{};
	std::string weatherFlag{};
	bool state = true;
};

struct InteriorToggleInformation // not final. pair isn't best idea. Will get back to it after weather
{
	std::string effectName{};
	std::pair<RE::FormID, std::string> interiorCell{}; // FormID + Plugin. If not a specific cell, place 0 or something
	bool state = true;
};

struct TimeToggleInformation
{
	std::string effectName{};
	float startTime = 0.f;
	float stopTime = 0.f;
	bool state = true;
};

class Manager : public ISingleton<Manager>
{
	// class for main functions used for all features

public:

	enum class Feature : std::uint32_t
	{
		kMenu,
		kWeather,
		kInterior,
		kTime
	};

	void parseJSONPreset(const std::string& presetName);

	void serializeJSONPreset(const std::string& presetName);

	void toggleEffectMenu(const std::set<std::string>& openMenus);

	std::vector<std::string> enumeratePresets();
	std::vector<std::string> enumerateEffects();
	std::vector<std::string> enumerateMenus();

	void toggleEffectWeather();

	std::vector<MenuToggleInformation> getMenuToggleInfo() const { return m_menuToggleInfo; }
	void setMenuToggleInfo(const std::vector<MenuToggleInformation>& info) { m_menuToggleInfo = info; }

private:
	std::string getPresetPath(const std::string& presetName);

	static float GetCurrentGameTime();

	void toggleEffect(const char* technique, bool state) const;

	std::vector<MenuToggleInformation> m_menuToggleInfo;
	//std::vector<WeatherToggleInformation> m_weatherToggleInfo;
	std::unordered_map<std::pair<std::uint32_t, std::string>, WeatherToggleInformation> m_weatherToggleInfo;

	std::vector<InteriorToggleInformation> m_interiorToggleInfo;
	std::vector<TimeToggleInformation> m_timeToggleInfo;

	std::pair<RE::TESWorldSpace*, WeatherToggleInformation> m_lastWs;
private:
	template<typename T>
	std::string serializeVector(const std::string& key, const std::vector<T>& vec);

	template<typename... Args>
	std::string serializeArbitraryVector(const Args&... args);

	template<typename... Args>
	void deserializeArbitraryVector(const std::string& buf, Args&... args);

};

extern reshade::api::effect_runtime* s_pRuntime;