#ifndef _CRY_VIEW_H_
#define _CRY_VIEW_H_

#include "CCEFViewBase.h"

namespace CEFPlugin
{

  class CCryView : public CCEFViewBase
  {
  public:
    CCryView(int width, int height, std::string url = "http://www.google.fr");
    ~CCryView(); 
  };
}

#endif
