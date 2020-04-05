#pragma once

#include "CharacterState.h"
#include "Vector2.h"

enum StateFlags : long long
{
	Clear = 0L,
	IsPlayingAnimation = 1L,
	IsCrouching = 2L,
	IsGrabbingBlock = 4L,
	IsGrabbingWall = 8L,
	IsGliding = 16L,
	IsSwimming = 32L,
	IsBashing = 64L,
	IsCarrying = 128L,
	IsStomping = 256L,
	IsSuspended = 512L,
	IsDashing = 1024L,
	IsStandingOnEdge = 2048L,
	IsUnderwater = 4096L,
	CannotMove = 8192L,
	IsPerformingCinematic = 16384L,
	IsInteracting = 32768L,
	IsRiding = 65536L,
	IsInputLocked = 131072L,
	IsDigging = 262144L,
	IsGrabbingSurface = 524288L,
	IsGrabbingRope = 1048576L,
	IsChargeJumping = 2097152L,
	IsCastingSpell = 4194304L,
	IsUsingLever = 8388608L,
	IsRacing = 16777216L,
	IsUsingMelee = 33554432L,
	IsPerformingCombo = 67108864L,
	IsSpiritLeashing = 134217728L,
	IsFalling = 268435456L,
	IsDisabledDueToDamage = 536870912L,
	IsFeatherFlapping = 1073741824L,
	IsBowAttacking = 2147483648L,
	IsAttacking = 4294967296L,
	IsHolding = 8589934592L,
	IsStressTesting = 17179869184L,
	IsThrowing = 34359738368L,
	CanGrabSomething = 68719476736L,
	IsLeverBlockingInput = 137438953472L,
	IsPickingUp = 274877906944L,
	IsUsingHeldItem = 549755813888L,
	IsTouchingDamageColliders = 1099511627776L,
	IsTeleporting = 2199023255552L,
	IsBowAttackingAndNotCancelable = 4398046511104L,

	// Really, VS?
	BlockInputStateFlag = 137439133696L,
	// Really, VS?

	BlockInvincibility = 0L,
	BlockAirNoDeceleration = 0L,
	BlockApplyFrictionToSpeed = 16384L,
	BlockCrushDetector = 49153L,
	BlockSpriteRotater = 0L,
	BlockDamageReciever = 16385L,
	BlockJumpSustain = 16385L,
	BlockUpwardsDeceleration = 16385L,
	BlockForceController = 16385L,
	BlockGravity = 81921L,
	BlockGravityToGround = 81953L,
	BlockSpellAbility = 3539008L,
	BlockSwimming = 0L,
	BlockDigging = 138461184L,
	BlockDash = 1623318981L,
	BlockGetAbility = 532753893L,
	BlockLaunch = 142671968L,
	BlockRiding = 12641765L,
	BlockSpell = 4399266054244L,
	BlockGrenadeSpell = 4403561557221L,
	BlockSpiritLeash = 13173223L,
	BlockBow = 1746141284L,
	BlockHammer = 2200235475008L,
	BlockMelee = 3025407377504L,
	BlockCombo = 3024730832960L,
	BlockGrabRope = 2218518970368L,
	BlockGrabSurface = 2231274373188L,
	BlockInstantStop = 536887329L,
	BlockLeftRightMovement = 53249L,
	BlockBash = 4398228226053L,
	BlockLooking = 2252603425L,
	BlockLever = 4260197L,
	BlockInteraction = 138412389L,
	BlockFootsteps = 65569L,
	BlockWallSlide = 1099517510129L,
	BlockCarry = 4260192L,
	BlockHolding = 32L,
	BlockFall = 376929L,
	BlockGrabBlock = 2199027515873L,
	BlockIdle = 115941L,
	BlockRun = 50405L,
	BlockCrouching = 34498168225L,
	BlockWallGrabbing = 3305082733025L,
	BlockJumping = 38060337L,
	BlockDoubleJump = 38011297L,
	BlockGliding = 4471270508009L,
	BlockWallJump = 4211121L,
	BlockChargeJump = 147112421L,
	BlockStandingOnEdge = 4194721L,
	BlockPushAgainstWall = 3298534883489L,
	BlockEdgeClamber = 161L,
	BlockTeleport = 135004192L,
	BlockChakramSpell = 148111364L,
	BlockMeditateSpell = 8699941L,
	BlockTurretSpell = 146931716L,
	BlockFeatherFlap = 4466975540713L,
	BlockAbilityUI = 0L,
	BlockShrineCombat = 2203341291520L,
	ResetComboCooldown = 2149056584L
};
#pragma pack(push, 1)

class SeinLogicCycle
{
public:

	// 0x0000 - 0x0017 
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18
	bool m_hasStateFlags;

	// 0x19
	bool m_hasRestrictZoneMask;

	// 0x20 - 0x27
	StateFlags m_StateFlags;
	
	// 0x28 - 0x2B
	unsigned long m_restrictZoneMask;

	// 0x2C 
	bool m_isTouchingDamageColliders;

	// 0x2D
	bool m_isAllowedNonZeroZPosition;

	// 0x2E
	bool m_b002E;

	// 0x2F
	bool m_b002F;

	// 0x30 - 0x33
	int m_currentAutoExecutionOrder;

	// 0x34 - 0x37
	unsigned long m_dwUnk0034_0037;

	// 0x38 - 0x3F
	unsigned long long SoredList_int_CharacterState_m_states;

	// 0x40 - 0x47
	unsigned long long List_CharacterState_m_statesList;

	// 0x48 - 0x4F
	unsigned long long Dictionary_Type_int_m_executionOrders;

	// 0x50 - 0x57
	unsigned long long Dictionary_Type_IsAllowedDelegate_m_isAllowedDelegates;

	// 0x58
	bool m_hasRegisteredDelagates;

	// 0x59 - 0x5F
	unsigned char uc_Unk0059_005F[0x60 - 0x59];

	// 0x60 - 0x67
	unsigned long long List_Type_m_exclusiveActiveStateTypes;

	// 0x68 - 0x6F
	unsigned long long List_CharacterState_m_exclusiveActiveStates;

	// 0x70 - 0x77
	unsigned long long HashSet_CharacterState_m_exclusiveActiveStatesSet;

	// 0x78 - 0x7F
	CharacterState * m_exclusiveActiveState;

	// 0x80 
	bool ShowDebug;

	// 0x81
	bool m_b0081;

	// 0x82
	bool m_b0082;

	// 0x83 
	bool m_b0083;
	
	// 0x84 - 0x8B
	Vector2 m_Scroll;
protected:
private:
};
#pragma pack(pop)