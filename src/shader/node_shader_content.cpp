#include "node_shader_content.h"

NodeShaderContent::NodeShaderContent()
{
    layout = new QVBoxLayout();
    this->layout->setContentsMargins(0,0,0,0);
    this->setLayout(this->layout);
}
