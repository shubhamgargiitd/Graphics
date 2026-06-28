#pragma once
#include <QObject> 
#include <memory>
#include "tools/tool.h"
#include "tools/individual_tools/circle_tool.h"
#include "tools/individual_tools/eraser_tool.h"
#include "tools/individual_tools/move_tool.h"
#include "tools/individual_tools/text_tool.h"
#include "tools/individual_tools/rectangle_tool.h"
#include "tools/individual_tools/hexagon_tool.h"
#include "tools/individual_tools/line_tool.h"
#include "tools/individual_tools/rounded_rectangle_tool.h"
#include "tools/individual_tools/freehand_tool.h"
#include "tools/individual_tools/resize_tool.h"

class ToolManager:public QObject
{
    Q_OBJECT

    public:
        ToolManager();
        std::shared_ptr<Tool> current_tool_;
        std::shared_ptr<CircleTool> circle_tool_;
        std::shared_ptr<EraserTool> eraser_tool_;
        std::shared_ptr<MoveTool> move_tool_;
        std::shared_ptr<TextTool> text_tool_;
        std::shared_ptr<RectangleTool> rectangle_tool_;
        std::shared_ptr<HexagonTool> hexagon_tool_;
        std::shared_ptr<LineTool> line_tool_;
        std::shared_ptr<RoundedRectangleTool> rounded_rectangle_tool_;
        std::shared_ptr<FreehandTool> freehand_tool_;
        std::shared_ptr<ResizeTool> resize_tool_;
        void SelectCircleTool();
        void SelectEraserTool();
        void SelectMoveTool();
        void SelectTextTool();
        void SelectRectangleTool();
        void SelectHexagonTool();
        void SelectLineTool();
        void SelectRoundedRectangleTool();
        void SelectFreehandTool();
        void SelectResizeTool();
};
