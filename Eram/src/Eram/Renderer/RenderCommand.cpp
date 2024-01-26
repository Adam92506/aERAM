#include "erpch.h"
#include "RenderCommand.h"

namespace Eram {

	Unique<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}