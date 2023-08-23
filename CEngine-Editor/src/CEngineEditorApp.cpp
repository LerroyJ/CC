#include <CEngine.h>
#include <CEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace CEngine {

	class CEngineEditor : public Application
	{
	public:
		CEngineEditor()
		{
			PushLayer(new EditorLayer());
		}

		~CEngineEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new CEngineEditor();
	}

}