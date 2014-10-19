
#include "ZViewpoint.h"

ZViewpoint::ZViewpoint(char* pName)
: ZVrmlNode(pName, NODE_VIEWPOINT)
{
    description = NULL;
    setFieldOfView(0.785398);
    setJump(true);
    setOrientation(ZRotation(0, 0, 1, 0));
    setPosition(ZVector3D(0, 0, 10));
}

ZViewpoint::ZViewpoint(const ZViewpoint& pRight): ZVrmlNode(NULL, NODE_VIEWPOINT)
{
    description = NULL;
    setFieldOfView(0.785398);
    setJump(true);
    setOrientation(ZRotation(0, 0, 1, 0));
    setPosition(ZVector3D(0, 0, 10));
    *this = pRight;
}

ZViewpoint::~ZViewpoint()
{
    delete[] description;
}

ZViewpoint& ZViewpoint::operator=(const ZViewpoint& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        setDescription(pRight.description);
        
        fieldOfView = pRight.fieldOfView;
        jump = pRight.jump;
        orientation = pRight.orientation;
        position = pRight.position;
    }

    return *this;
}

void ZViewpoint::setFieldOfView(float pFieldOfView)
{
    fieldOfView = pFieldOfView;  
}

void ZViewpoint::setJump(bool pJump)
{
    jump = pJump;  
}

void ZViewpoint::setOrientation(ZRotation pOrientation)
{
    orientation = pOrientation;  
}

void ZViewpoint::setPosition(ZVector3D pPosition)
{
    position = pPosition;  
}

void ZViewpoint::setDescription(const char* pDescription)
{
    delete[] description;
    if(pDescription != NULL)
    {        
        description = new char[strlen(pDescription)];
        strcpy(description, pDescription);
    } else {
        description = NULL;
    }
}

ZVrmlNode* ZViewpoint::clone()
{
    ZViewpoint* clone = new ZViewpoint(*this);

    return dynamic_cast<ZViewpoint*>(clone);
}

void ZViewpoint::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "fieldOfView") )
        setFieldOfView(value.vFloat);
    else if( !strcmp(fieldName, "jump") )
        setJump(value.vBool);
    else if( !strcmp(fieldName, "orientation") )
        setOrientation(value.vZRotation);
    else if( !strcmp(fieldName, "position") )
        setPosition(value.vZVector3D);
    else if( !strcmp(fieldName, "description") )
        setDescription(value.vString.c_str());
}

void ZViewpoint::action()
{
    ZVector3D target, up;

    const double s = sin(DEG2RAD(orientation.getAngle()));
    const double c = cos(DEG2RAD(orientation.getAngle()));
    const double t = 1.0 - c;
    const double distance = 20000.0 * 0.2;
    // Transform [0,0,1] by the orientation to determine sight line

    target.setX(t * orientation.getX() * orientation.getZ() + s * orientation.getY());
    target.setY(t * orientation.getY() * orientation.getZ() - s * orientation.getX());
    target.setZ(t * orientation.getZ() * orientation.getZ() + c);

    // Move along that vector the specified distance away from position[]
    target.setX( target.getX() * -distance + position.getX());
    target.setY( target.getY() * -distance + position.getY());
    target.setZ( target.getZ() * -distance + position.getZ());

    // Transform [0,1,0] by the orientation to determine up vector
    up.setX(t * orientation.getX() * orientation.getY() - s * orientation.getZ());
    up.setY(t * orientation.getY() * orientation.getY() + c);
    up.setZ(t * orientation.getY() * orientation.getZ() + s * orientation.getX());

    gluLookAt(position.getX(), position.getY(), position.getZ(),
              target.getX(), target.getY(), target.getZ(),
              up.getX(), up.getY(), up.getZ());
}

void ZViewpoint::addToBrowser(Browser* browser, Group* parent)
{
    Group* root;
    if(getName())
    {
        char* name = new char[256];
        snprintf(name,256,"Viewpoint (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("Viewpoint", parent, NULL);
        root->deactivate();
    }    
}

void ZViewpoint::print()
{

}

ostream &operator<<( ostream &output, const ZViewpoint &viewpoint )
{
    //output << "Viewpoint: "<< viewpoint.name << endl;
    output << "fieldOfView: "<< viewpoint.fieldOfView << endl;
    output << "jump: "<< viewpoint.jump << endl;
    //output << "orientation: "<< viewpoint.orientation << endl;
    //output << "position: "<< viewpoint.position << endl;
    output << "description: "<< viewpoint.description << endl;
    return output;
}

void ZViewpoint::move()
{
    
}
