#include "StdAfx.h"
#include "Nodes/G2FlowBaseNode.h"
 
class CFlowNode_Entity_Attach : public CFlowBaseNode<eNCT_Instanced>
{
public:
  enum EInputs
  {
    IN_Attach,
    IN_ParentId,
    IN_ChildId,
    IN_OffsetPos,
    IN_OffsetRot
  };

  enum EOutputs
  {
    OUT_Attached,
  };

  CFlowNode_Entity_Attach(SActivationInfo* pActInfo)
  {
    // CryLog("[Toggle Flownode] Creating new instance.");    
  };
 
  virtual IFlowNodePtr Clone(SActivationInfo *pActInfo)
  {
    return new CFlowNode_Entity_Attach(pActInfo);
  };
 
  virtual void GetMemoryUsage(ICrySizer* s) const
  {
     s->Add(*this);
  }
 
  virtual void GetConfiguration(SFlowNodeConfig& config)
  {
    static const SInputPortConfig in_config[] = {
      InputPortConfig_Void("Attach",_HELP("Perform attachment operation")),
      InputPortConfig<EntityId>("ParentId",_HELP("Parent entity Id")),
      InputPortConfig<EntityId>("ChildId",_HELP("Child entity Id")),
      InputPortConfig<Vec3>("OffsetPos",_HELP("Local position offset for the child.")),
      InputPortConfig<Vec3>("OffsetRot",_HELP("Local rotation offset for the child.")),
      {0}
    };
    static const SOutputPortConfig out_config[] = {
      OutputPortConfig_Void("Attached",_HELP("Triggered once the attachment is done.")),
      {0}
    };
    config.sDescription = _HELP( "Flow node used to attach a child entity to a parent, and trigger and event went done." );
    config.pInputPorts = in_config;
    config.pOutputPorts = out_config;
    config.SetCategory(EFLN_APPROVED);
  }
 
  virtual void ProcessEvent(EFlowEvent event, SActivationInfo* pActInfo)
  {
    if (event == eFE_Activate)
    {

      if (IsPortActive(pActInfo, IN_Attach))
      {
        CryLog("[Attach Flownode] Attaching child to parent...");

        // We retrieve the parent and the child entities Ids:
        EntityId parentId = GetPortEntityId(pActInfo,IN_ParentId);
        EntityId childId = GetPortEntityId(pActInfo,IN_ChildId);

        // Retrieving the real entities from the IDs:
        IEntity* parent = gEnv->pEntitySystem->GetEntity(parentId); 
        IEntity* child = gEnv->pEntitySystem->GetEntity(childId); 

        if(!parent || !child) {
          CryLog("[ERROR] Could not find parent or child entity in Nerv:Entity:Attach flow node.");
          return;
        }

        // Now that we have the parent and child entities,
        // we attach the child to the parent,
        // Note that we do not need to specify the attachment flags as we don't 
        // want to keep the world position, and we will actually use the
        // position and rotation offsets just after:
        parent->AttachChild(child);

        // Once the child is attached, we need to retrieve the position and rotation offsets:
        Vec3 pos = GetPortVec3(pActInfo,IN_OffsetPos);
        Vec3 rot = GetPortVec3(pActInfo,IN_OffsetRot);

        // Convert the rotation angle vector to a real quaternion object:
        Quat q = Quat::CreateRotationXYZ(Ang3(rot));

        // Now set the position and rotation of the child in local coords:
        child->SetPos(pos);
        child->SetRotation(q);

        // Once the setup is done, we trigger the output port:
        ActivateOutput(pActInfo, OUT_Attached, true);
      }
    }
  }
};
 
REGISTER_FLOW_NODE("Nerv:Entity:Attach", CFlowNode_Entity_Attach);
