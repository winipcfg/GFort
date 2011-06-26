#ifndef GFORT_PHYSICS_BOX2D_SETTINGS_H_
#define GFORT_PHYSICS_BOX2D_SETTINGS_H_

#include <Box2D/Box2D.h>

namespace GFort { namespace Physics
{

struct Box2dSettings
{
public:
    /// Constructor
    Box2dSettings() : 
      hz(60.0f),
      velocityIterations(8),
      positionIterations(1),
      enableWarmStarting(1),
      enableContinuous(1),
      singleStep(0)
    {
        paused_ = false;

        allowed_draw_shapes_ = true;
        allowed_draw_joints_ = true;
        allowed_draw_AABBs_ = false;
        allowed_draw_pairs_ = false;
        allowed_draw_COMs_ = false;

        allowed_draw_contact_points_ = false;
        allowed_draw_contact_normals_ = false;
        allowed_draw_contact_forces_ = false;
        allowed_draw_friction_forces_ = false;
        allowed_draw_stats_ = false;

        RefreshDebugFlag();
    }

    /// Pause the engine.
    void Pause()                            { paused_ = true; }

    /// Resume the engine.
    void Resume()                           { paused_ = false; }

    /// Returns true if physics engine is paused.
    const bool Paused() const               { return paused_; }

    /// Gets the debug flag.
    const uint32 GetDebugFlag() const       { return debug_flag_; }

protected:	
    /// Refresh the debug draw flags
    void RefreshDebugFlag();

public:
    // Stores various parameters
    float32     hz;
    int32       velocityIterations;
    int32       positionIterations;
    int32       enableWarmStarting;
    int32       enableContinuous;
    int32       singleStep;

protected:
    // Stores whether he physics engine is paused
    bool		paused_;

    // Stores various flag settings
    bool		allowed_draw_shapes_;
    bool		allowed_draw_joints_;
    bool		allowed_draw_AABBs_;
    bool		allowed_draw_pairs_;
    bool		allowed_draw_COMs_;

    bool		allowed_draw_contact_points_;
    bool		allowed_draw_contact_normals_;
    bool		allowed_draw_contact_forces_;
    bool		allowed_draw_friction_forces_;
    bool		allowed_draw_stats_;

private:
    // Stores combined flag settings
    uint32		debug_flag_;
};

inline void Box2dSettings::RefreshDebugFlag()
{
    debug_flag_ = 0;
    debug_flag_ += allowed_draw_shapes_			* b2DebugDraw::e_shapeBit;
    debug_flag_ += allowed_draw_joints_			* b2DebugDraw::e_jointBit;
    debug_flag_ += allowed_draw_AABBs_			* b2DebugDraw::e_aabbBit;
    debug_flag_ += allowed_draw_pairs_			* b2DebugDraw::e_pairBit;
    debug_flag_ += allowed_draw_COMs_			* b2DebugDraw::e_centerOfMassBit;
}

} } // namespace

#endif // GFORT_PHYSICS_BOX2D_SETTINGS_H_
