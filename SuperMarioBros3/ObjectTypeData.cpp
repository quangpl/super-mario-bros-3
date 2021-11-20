#include "ObjectTypeData.h"

const ObjectType ObjectTypeData::SmallMario = ObjectType::CreateObjectType(1, "SmallMario");
const ObjectType ObjectTypeData::BigMario = ObjectType::CreateObjectType(2, "BigMario");
const ObjectType ObjectTypeData::FireMario = ObjectType::CreateObjectType(3, "FireMario");
const ObjectType ObjectTypeData::RaccoonMario = ObjectType::CreateObjectType(4, "RaccoonMario");

const ObjectType ObjectTypeData::BigLuigi = ObjectType::CreateObjectType(5, "BigLuigi");

const ObjectType ObjectTypeData::MarioFireBall = ObjectType::CreateObjectType(11, "MarioFireBall");
const ObjectType ObjectTypeData::MarioTailed = ObjectType::CreateObjectType(12, "MarioTailed");

const ObjectType ObjectTypeData::Goomba = ObjectType::CreateObjectType(101, "Goomba");

const ObjectType ObjectTypeData::Koopas = ObjectType::CreateObjectType(121, "Koopas");
const ObjectType ObjectTypeData::KoopasCrouch = ObjectType::CreateObjectType(122, "KoopasCrouch");
const ObjectType ObjectTypeData::KoopasPassenger = ObjectType::CreateObjectType(123, "KoopasPassenger");
const ObjectType ObjectTypeData::KoopasImposter = ObjectType::CreateObjectType(124, "KoopasImposter");
const ObjectType ObjectTypeData::KoopasJumping = ObjectType::CreateObjectType(125, "KoopasJumping");

const ObjectType ObjectTypeData::RedKoopas = ObjectType::CreateObjectType(141, "RedKoopas");
const ObjectType ObjectTypeData::RedKoopasCrouch = ObjectType::CreateObjectType(142, "RedKoopasCrouch");
const ObjectType ObjectTypeData::RedKoopasPassenger = ObjectType::CreateObjectType(143, "RedKoopasPassenger");
const ObjectType ObjectTypeData::RedKoopasImposter = ObjectType::CreateObjectType(144, "RedKoopasImposter");
const ObjectType ObjectTypeData::RedKoopasJumping = ObjectType::CreateObjectType(145, "RedKoopasJumping");
const ObjectType ObjectTypeData::RedKoopasFlying = ObjectType::CreateObjectType(145, "RedKoopasFlying");

const ObjectType ObjectTypeData::Venus = ObjectType::CreateObjectType(161, "Venus");
const ObjectType ObjectTypeData::VenusFireBall = ObjectType::CreateObjectType(162, "VenusFireBall");
const ObjectType ObjectTypeData::RedVenus = ObjectType::CreateObjectType(163, "RedVenus");
const ObjectType ObjectTypeData::Piranha = ObjectType::CreateObjectType(164, "Piranha");

const ObjectType ObjectTypeData::RedGoomba = ObjectType::CreateObjectType(181, "RedGoomba");

const ObjectType ObjectTypeData::BoomerangBrother = ObjectType::CreateObjectType(201, "BoomerangBrother");
const ObjectType ObjectTypeData::Boomerang = ObjectType::CreateObjectType(202, "Boomerang");

const ObjectType ObjectTypeData::EndmapReward = ObjectType::CreateObjectType(1001, "EndmapReward");
const ObjectType ObjectTypeData::QuestionBlock = ObjectType::CreateObjectType(1002, "QuestionBlock");
const ObjectType ObjectTypeData::Spawner = ObjectType::CreateObjectType(1003, "Spawner");

const ObjectType ObjectTypeData::SolidBlock = ObjectType::CreateObjectType(5001, "SolidBlock");
const ObjectType ObjectTypeData::GhostBlock = ObjectType::CreateObjectType(5002, "GhostBlock");
const ObjectType ObjectTypeData::VoidBlock = ObjectType::CreateObjectType(5003, "Void");
const ObjectType ObjectTypeData::Pipe = ObjectType::CreateObjectType(5004, "Pipe");
const ObjectType ObjectTypeData::MovingPlatform = ObjectType::CreateObjectType(5005, "MovingPlatform");

const ObjectType ObjectTypeData::RedMushroom = ObjectType::CreateObjectType(10001, "RedMushroom");
const ObjectType ObjectTypeData::GreenMushroom = ObjectType::CreateObjectType(10002, "GreenMushroom");
const ObjectType ObjectTypeData::RaccoonLeaf = ObjectType::CreateObjectType(10003, "RaccoonLeaf");
const ObjectType ObjectTypeData::FireFlower = ObjectType::CreateObjectType(10004, "FireFlower");
const ObjectType ObjectTypeData::QuestionCoin = ObjectType::CreateObjectType(10005, "QuestionCoin");
const ObjectType ObjectTypeData::PSwitch = ObjectType::CreateObjectType(10006, "PSwitch");

const ObjectType ObjectTypeData::Coin = ObjectType::CreateObjectType(10011, "Coin");
const ObjectType ObjectTypeData::Brick = ObjectType::CreateObjectType(10012, "Brick");

const ObjectType ObjectTypeData::BeginPortal = ObjectType::CreateObjectType(20011, "BeginPortal");
const ObjectType ObjectTypeData::EndPortal = ObjectType::CreateObjectType(20012, "EndPortal");

const ObjectType ObjectTypeData::TinyMario = ObjectType::CreateObjectType(30001, "TinyMario");
const ObjectType ObjectTypeData::Tree = ObjectType::CreateObjectType(30002, "Tree");
const ObjectType ObjectTypeData::Node = ObjectType::CreateObjectType(30003, "Node");

bool ObjectTypeData::IsTile(ObjectType type)
{
    bool normalTile = type == DEFAULT_TILE_ID;
    bool questionTile = type == QuestionBlock;
    bool solidBlock = type == SolidBlock;
    bool ghostBlock = type == GhostBlock;
    bool pipe = type == Pipe;
    bool brick = type == Brick;
    return normalTile || questionTile || solidBlock || ghostBlock || pipe || brick;
}

bool ObjectTypeData::IsMario(ObjectType obj)
{
    bool isSmall = obj == SmallMario;
    bool isBig = obj == BigMario;
    bool isFire = obj == FireMario;
    bool isRaccoon = obj == RaccoonMario;

    bool isBigLuigi = obj == BigLuigi;

    return isSmall || isBig || isFire || isRaccoon || isBigLuigi;
}

bool ObjectTypeData::IsMarioWeapon(ObjectType obj)
{
    bool isBullet = obj == MarioFireBall;
    bool isTail = obj == MarioTailed;
    bool isShell = obj == KoopasPassenger || obj == KoopasImposter;
    bool voidblock = obj == VoidBlock;
    return isBullet || isTail || isShell || voidblock;
}

bool ObjectTypeData::IsEnemy(ObjectType obj)
{
    bool goomba = obj == Goomba;
    bool redgoomba = obj == RedGoomba;
    bool koopas = obj == Koopas || obj == KoopasCrouch || obj == KoopasImposter || obj == KoopasJumping;
    bool redkoopas = obj == RedKoopas || obj == RedKoopasCrouch || obj == RedKoopasImposter || obj == RedKoopasJumping;
    bool venus = obj == Venus || obj == VenusFireBall || obj == RedVenus;
    bool piranha = obj == Piranha;
    bool voidblock = obj == VoidBlock;
    bool boomerangBrother = obj == Boomerang || obj == BoomerangBrother;
    return goomba || redgoomba || koopas || redkoopas || venus || piranha || voidblock || boomerangBrother;
}

bool ObjectTypeData::IsPowerUpItem(ObjectType obj)
{
    bool mushroom = obj == RedMushroom;
    bool greenmushroom = obj == GreenMushroom;
    bool leaf = obj == RaccoonLeaf;
    return mushroom || greenmushroom || leaf;
}

bool ObjectTypeData::IsMapObject(ObjectType obj)
{
    bool isVoid = obj == VoidBlock;
    bool isGhost = obj == GhostBlock;
    bool isSolid = obj == SolidBlock;
    return isVoid || isGhost || isSolid;
}
