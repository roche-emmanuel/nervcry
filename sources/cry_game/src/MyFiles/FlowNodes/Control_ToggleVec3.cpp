#include "StdAfx.h"
#include "Nodes/G2FlowBaseNode.h"
 
class CFlowNode_ToggleVec3 : public CFlowBaseNode<eNCT_Instanced>
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

  CFlowNode_ToggleVec3(SActivationInfo* pActInfo) : _state(0)
  {
    // CryLog("[ToggleEntity Flownode] Creating new instance.");    
  };
 
  virtual IFlowNodePtr Clone(SActivationInfo *pActInfo)
  {
    return new CFlowNode_ToggleVec3(pActInfo);
  };
 
  virtual void GetMemoryUsage(ICrySizer* s) const
  {
     s->Add(*this);
  }
 
  virtual void GetConfiguration(SFlowNodeConfig& config)
  {
    static const SInputPortConfig in_config[] = {
      InputPortConfig_Void("Trigger",_HELP("Toggle the current value between vec1 and vec2")),
      InputPortConfig<Vec3>("Value1",_HELP("The initial Vec3 contained in the flownode")),
      InputPortConfig<Vec3>("Value2",_HELP("The secondary Vec3 contained in the flownode")),
      {0}
    };
    static const SOutputPortConfig out_config[] = {
      OutputPortConfig<Vec3>("CurrentValue",_HELP("The current Vec3 at use after trigger event.")),
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
        // CryLog("[ToggleEntity Flownode] Activating trigger input...");

        // Toggle the state:
        _state = _state==0 ? 1 : 0;

        if(_state==0) {
          // In that case we need to activate the Value1
          // CryLog("[ToggleEntity Flownode] Selecting Entity1");
          ActivateOutput(pActInfo, OUT_CurrentValue, GetPortVec3(pActInfo, IN_Value1));
        }
        else {
          // Here we need to activate the Value2.
          // CryLog("[ToggleEntity Flownode] Selecting Entity2");
          ActivateOutput(pActInfo, OUT_CurrentValue, GetPortVec3(pActInfo, IN_Value2));
        }
      }
    }
  }
};
 
REGISTER_FLOW_NODE("Nerv:Control:ToggleVec3", CFlowNode_ToggleVec3);
