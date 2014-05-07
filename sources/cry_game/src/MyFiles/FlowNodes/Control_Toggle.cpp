#include "StdAfx.h"
#include "Nodes/G2FlowBaseNode.h"
 
class CFlowNode_Toggle : public CFlowBaseNode<eNCT_Instanced>
{
protected:
  // Store the current state of this toggle node, the value of the state can be 0 or 1 only.
  // The state is always initialized to 0.
  unsigned int _state;

public:
  enum EInputs
  {
    IN_Trigger,
    IN_Value1,
    IN_Value2,
  };

  enum EOutputs
  {
    OUT_CurrentValue,
  };

  CFlowNode_Toggle(SActivationInfo* pActInfo) : _state(0)
  {
    // CryLog("[Toggle Flownode] Creating new instance.");    
  };
 
  virtual IFlowNodePtr Clone(SActivationInfo *pActInfo)
  {
    return new CFlowNode_Toggle(pActInfo);
  };
 
  virtual void GetMemoryUsage(ICrySizer* s) const
  {
     s->Add(*this);
  }
 
  virtual void GetConfiguration(SFlowNodeConfig& config)
  {
    static const SInputPortConfig in_config[] = {
      InputPortConfig_Void("Trigger",_HELP("Toggle the current value between value1 and value2")),
      InputPortConfig_Void("Value1",_HELP("The initial value contained in the flownode")),
      InputPortConfig_Void("Value2",_HELP("The secondary value contained in the flownode")),
      {0}
    };
    static const SOutputPortConfig out_config[] = {
      OutputPortConfig_Void("CurrentValue",_HELP("The current value at use after trigger event.")),
      {0}
    };
    config.sDescription = _HELP( "Flow node used to toggle between two values each time a trigger is received." );
    config.pInputPorts = in_config;
    config.pOutputPorts = out_config;
    config.SetCategory(EFLN_APPROVED);
  }
 
  virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
  {
    if (event == eFE_Activate)
    {

      if (IsPortActive(pActInfo, IN_Trigger))
      {
        // CryLog("[Toggle Flownode] Activating trigger input...");

        // Toggle the state:
        _state = _state==0 ? 1 : 0;

        if(_state==0) {
          // In that case we need to activate the Value1
          // CryLog("[Toggle Flownode] Selecting Value1");
          ActivateOutput(pActInfo, OUT_CurrentValue, GetPortAny(pActInfo, IN_Value1));
        }
        else {
          // Here we need to activate the Value2.
          // CryLog("[Toggle Flownode] Selecting Value2");
          ActivateOutput(pActInfo, OUT_CurrentValue, GetPortAny(pActInfo, IN_Value2));
        }
      }
    }
  }
};
 
REGISTER_FLOW_NODE("Nerv:Control:Toggle", CFlowNode_Toggle);
