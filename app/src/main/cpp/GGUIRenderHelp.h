//----------------------------------------------------------------
#ifndef _GGUIRenderHelp_h_
#define _GGUIRenderHelp_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GGUIComponentText;
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleImage(int nImagesetId, int nImageRectId, const GGUIRect& kAbsRect, const GGUIColor& kColor, bool bSwapX, bool bSwapY);
void GGUIRenderHelp_SimpleText(const char* szText, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const SoTinyString& kFontName, const GGUIColor& kColor);
//----------------------------------------------------------------
#endif //_GGUIRenderHelp_h_
//----------------------------------------------------------------
