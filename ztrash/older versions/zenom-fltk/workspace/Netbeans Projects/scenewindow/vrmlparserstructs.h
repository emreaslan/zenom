/* 
 * File:   vrmlparserstructs.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 3:35 PM
 */

#ifndef _VRMLPARSERSTRUCTS_H
#define	_VRMLPARSERSTRUCTS_H

#include "Array.h"
#include "utils.h"

# include <openvrml/vrml97_grammar.h>
# include <openvrml/browser.h>
# include <fstream>

#include <iostream>
#include <sstream>
#include <string>

#include <stack>


#include "ZNotSupportedNode.h"
#include "ZTransform.h"
#include "ZGroup.h"
#include "ZShape.h"
#include "ZViewpoint.h"
#include "ZNavigationInfo.h"
#include "ZDirectionalLight.h"
#include "ZPointLight.h"
#include "ZSpotLight.h"



using namespace std;
using namespace boost::spirit;
using namespace openvrml;

struct ZVrmlActions : openvrml::null_vrml97_parse_actions
{

    ZAttribute attribute;
    Array<ZVrmlNode *>* nodes;
    Array<ZVrmlNode *> completedNodes;
    stack<ZVrmlNode *> parents;
    std::string fieldId;
    Array<ZViewpoint*>* viewpoints;
    Array<ZNavigationInfo*>* navigationInfos;

    ZVrmlActions(Array<ZVrmlNode *>* nodeArray, Array<ZViewpoint *>* pViewpoints, Array<ZNavigationInfo *>* pNavigationInfos)
    : nodes(nodeArray), viewpoints(pViewpoints), navigationInfos(pNavigationInfos),
      on_node_start(*this),
      on_node_finish(*this),
      on_use(*this),
      on_field_start(*this),
      on_sfbool(*this),
      on_sfcolor(*this),
      on_sffloat(*this),
      on_sfint32(*this),
      on_sfrotation(*this),
      on_sfstring(*this),
      on_sftime(*this),
      on_sfvec2f(*this),
      on_sfvec3f(*this),
      on_mfcolor(*this),
      on_mffloat(*this),
      on_mfint32(*this),
      on_mfrotation(*this),
      on_mfstring(*this),
      on_mftime(*this),
      on_mfvec2f(*this),
      on_mfvec3f(*this)
    {}

    struct on_node_start_t
    {
        explicit on_node_start_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::string & node_name_id,
                        const std::string & node_type_id) const
        {
            ZVrmlNode* znode;
            if( !strcmp(node_type_id.c_str(), "Transform") )
            {
                znode = new ZTransform();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Group") )
            {
                znode = new ZGroup();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Shape") )
            {
                znode = new ZShape();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Box") )
            {
                znode = new ZBox();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Cone") )
            {
                znode = new ZCone();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Sphere") )
            {
                znode = new ZSphere();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Cylinder") )
            {
                znode = new ZCylinder();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "PointSet") )
            {
                znode = new ZPointSet();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "IndexedLineSet") )
            {
                znode = new ZIndexedLineSet();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "IndexedFaceSet") )
            {
                znode = new ZIndexedFaceSet();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "ElevationGrid") )
            {
                znode = new ZElevationGrid();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Appearance") )
            {
                znode = new ZAppearance();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Material") )
            {
                znode = new ZMaterial();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Coordinate") )
            {
                znode = new ZCoordinate();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Color") )
            {
                znode = new ZColorNode();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Normal") )
            {
                znode = new ZNormal();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "Viewpoint") )
            {
                znode = new ZViewpoint();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "NavigationInfo") )
            {
                znode = new ZNavigationInfo();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "DirectionalLight") )
            {
                znode = new ZDirectionalLight();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "PointLight") )
            {
                znode = new ZPointLight();
                parent.parents.push(znode);
            }
            else if( !strcmp(node_type_id.c_str(), "SpotLight") )
            {
                znode = new ZSpotLight();
                parent.parents.push(znode);
            }
            else
            {
                // Sorry my man, no support remaining nodes
                znode = new ZNotSupportedNode(node_type_id.c_str());
                parent.parents.push(znode);
                printf("Unsopperted Node: %s\n", node_type_id.c_str());
            }

            
            if (!node_name_id.empty())
            {
                znode->setName(node_name_id.c_str());
            }
        }
        ZVrmlActions &parent;
    } on_node_start;

    // ---------------------------------------------------------------------//


    struct on_node_finish_t
    {
        explicit on_node_finish_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()() const
        {

            ZVrmlNode *child = parent.parents.top();
            parent.parents.pop();
            parent.completedNodes.appendElement(child);

            // collect view points for opengl
            ZViewpoint* viewpoint = dynamic_cast<ZViewpoint *>(child);
            ZNavigationInfo* navigationInfo = dynamic_cast<ZNavigationInfo *>(child);
            if(viewpoint != NULL)
            {                
                parent.viewpoints->appendElement(viewpoint);
            }
            else if(navigationInfo != NULL)
            {
                parent.navigationInfos->appendElement(navigationInfo);
            }
            else
            {
                if(!parent.parents.empty())
                {    
                    parent.parents.top()->addChild(child);
                }
                else
                {
                    parent.nodes->appendElement(child);
                }
            }
        }
        
        ZVrmlActions &parent;
    } on_node_finish;


    // ---------------------------------------------------------------------//

    struct on_use_t
    {
        explicit on_use_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::string& node_name_id) const
        {

            // Find object and get clone
            for(int i = 0; i < parent.completedNodes.getNumElements(); ++i)
            {
                if(parent.completedNodes.getElement(i)->getName())
                {
                    if( !strcmp(node_name_id.c_str(), parent.completedNodes.getElement(i)->getName()) )
                    {
                        ZVrmlNode *clone = parent.completedNodes.getElement(i)->clone();
                        if(!parent.parents.empty())
		        {    
		            parent.parents.top()->addChild(clone);
		        }
		        else
		        {
		            parent.nodes->appendElement(clone);
		        }
                        break;
                    } 
                } 
            }
              
        }
        ZVrmlActions &parent;
    } on_use;

    // ---------------------------------------------------------------------//

    struct on_field_start_t
    {
        explicit on_field_start_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::string & field_name_id,
                            field_value::type_id /* field_type */) const
        {
            parent.fieldId = field_name_id;
        }
        ZVrmlActions &parent;
    } on_field_start;


    // ---------------------------------------------------------------------//


    struct on_sfnode_t {
            void operator()(bool /* null */) const { }
        } on_sfnode;


    // ---------------------------------------------------------------------//
    struct on_sfbool_t
    {
        explicit on_sfbool_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(bool pBool) const
        {
            parent.attribute.vBool = pBool;
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfbool;
    // ---------------------------------------------------------------------//

    // ---------------------------------------------------------------------//
    struct on_sfcolor_t
    {
        explicit on_sfcolor_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const openvrml::color& pColor) const
        {
            parent.attribute.vZColor = ZColor(pColor.r(), pColor.g(), pColor.b());
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfcolor;
    // ---------------------------------------------------------------------//

    // ---------------------------------------------------------------------//
    struct on_sffloat_t
    {
        explicit on_sffloat_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const float pFloat) const
        {
            parent.attribute.vFloat = pFloat;
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sffloat;
    // ---------------------------------------------------------------------//




    


        struct on_sfimage_t {
            void operator()(const image &) const {}
        } on_sfimage;









    // ---------------------------------------------------------------------//
    struct on_sfint32_t
    {
        explicit on_sfint32_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const int32 pInt) const
        {
            parent.attribute.vInt = pInt;
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfint32;
    // ---------------------------------------------------------------------//

    // ---------------------------------------------------------------------//
    struct on_sfrotation_t
    {
        explicit on_sfrotation_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const rotation & pRotation) const
        {
            parent.attribute.vZRotation = ZRotation(pRotation);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfrotation;
    // ---------------------------------------------------------------------//

    // ---------------------------------------------------------------------//
    struct on_sfstring_t
    {
        explicit on_sfstring_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::string &pString) const
        {
            cout << pString <<endl;
            parent.attribute.vString = pString;
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfstring;
    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//
    struct on_sftime_t
    {
        explicit on_sftime_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const double pDouble) const
        {
            parent.attribute.vDouble = pDouble;
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sftime;
    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//
    struct on_sfvec2f_t
    {
        explicit on_sfvec2f_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const vec2f &pVec2f) const
        {
            parent.attribute.vZVector2D = ZVector2D(pVec2f.x(),pVec2f.y());
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfvec2f;
    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//
    struct on_sfvec3f_t
    {
        explicit on_sfvec3f_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const vec3f &pVec3f) const
        {
            parent.attribute.vZVector3D = ZVector3D(pVec3f);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }
        ZVrmlActions &parent;
    } on_sfvec3f;

    // ---------------------------------------------------------------------//

       
        
        /////////////////////   MULTI /////////////////////


    // ---------------------------------------------------------------------//

    struct on_mfcolor_t
    {
        explicit on_mfcolor_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<openvrml::color> &colors) const
        {            
            parent.attribute.vZColors = new Array<ZColor>;
            for(int i = 0; i < colors.size(); ++i)
                parent.attribute.vZColors->appendElement(colors[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);            
        }

        ZVrmlActions &parent;
    } on_mfcolor;
    
    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//

    struct on_mffloat_t
    {
        explicit on_mffloat_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<float> &floats) const
        {

            parent.attribute.vDoubles = new Array<double>;
            for(int i = 0; i < floats.size(); ++i)
                parent.attribute.vDoubles->appendElement(floats[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);

        }

        ZVrmlActions &parent;
    } on_mffloat;

    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//

    struct on_mfint32_t
    {
        explicit on_mfint32_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<int32> &ints) const
        {

            parent.attribute.vIntegers = new Array<int>;
            for(int i = 0; i < ints.size(); ++i)
                parent.attribute.vIntegers->appendElement(ints[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);

        }

        ZVrmlActions &parent;
    } on_mfint32;

    // ---------------------------------------------------------------------//



        struct on_mfnode_t {
            void operator()() const {}
        } on_mfnode;





    // ---------------------------------------------------------------------//

    struct on_mfrotation_t
    {
        explicit on_mfrotation_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<rotation> &rotations) const
        {
            parent.attribute.vZRotations = new Array<ZRotation>;
            for(int i = 0; i < rotations.size(); ++i)
                parent.attribute.vZRotations->appendElement(rotations[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);

        }

        ZVrmlActions &parent;
    } on_mfrotation;

    // ---------------------------------------------------------------------//




    // ---------------------------------------------------------------------//

    struct on_mfstring_t
    {
        explicit on_mfstring_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<std::string> &strings) const
        {
            // TODO Strings
            /*
            parent.attribute.vZRotations = new Array<ZRotation>;
            for(int i = 0; i < rotations.size(); ++i)
                parent.attribute.vZRotations->appendElement(rotations[i]);
             parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
             * */
        }

        ZVrmlActions &parent;
    } on_mfstring;

    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//

    struct on_mftime_t
    {
        explicit on_mftime_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<double> &doubles) const
        {
            parent.attribute.vDoubles = new Array<double>;
            for(int i = 0; i < doubles.size(); ++i)
                parent.attribute.vDoubles->appendElement(doubles[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }

        ZVrmlActions &parent;
    } on_mftime;

    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//

    struct on_mfvec2f_t
    {
        explicit on_mfvec2f_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<vec2f> &vec2fs) const
        {
            parent.attribute.vZVector2Ds = new Array<ZVector2D>;
            for(int i = 0; i < vec2fs.size(); ++i)
                parent.attribute.vZVector2Ds->appendElement(vec2fs[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }

        ZVrmlActions &parent;
    } on_mfvec2f;

    // ---------------------------------------------------------------------//


    // ---------------------------------------------------------------------//

    struct on_mfvec3f_t
    {
        explicit on_mfvec3f_t(ZVrmlActions& pParent)
        : parent(pParent)
        {}

        void operator()(const std::vector<vec3f> &vec3fs) const
        {
            parent.attribute.vZVector3Ds = new Array<ZVector3D>();
            for(int i = 0; i < vec3fs.size(); ++i)
                parent.attribute.vZVector3Ds->appendElement(vec3fs[i]);
            parent.parents.top()->setField(parent.fieldId.c_str(), parent.attribute);
        }

        ZVrmlActions &parent;

    } on_mfvec3f;

    // ---------------------------------------------------------------------//

};


    // ---------------------------------------------------------------------//

       
        
        /////////////////////   ERROR HANDLER   /////////////////////


    // ---------------------------------------------------------------------//

struct ZVrmlParseError
{
    explicit ZVrmlParseError()
    {
        errorString = new ostringstream();
    }


    ~ZVrmlParseError()
    {

    }

    const std::string getError() const
    {
        return errorString->str();
    }

    template <typename ScannerT, typename ErrorT>
    boost::spirit::error_status<> operator()(const ScannerT & scan, const ErrorT & err) const
    {
        using std::ostringstream;
        using std::endl;
        using boost::spirit::error_status;
        using boost::spirit::file_position;


        const file_position fpos = err.where.get_position();
        if (err.descriptor == rotation_axis_not_normalized)
        {
            *(this->errorString) << fpos.file << ':' << fpos.line << ':'
                       << fpos.column << ": warning: "
                       << vrml97_parse_error_msg(err.descriptor)
                       << endl;
            scan.first = err.where;
            return error_status<>(error_status<>::accept, 0);
        }

        *(this->errorString) << fpos.file << ':' << fpos.line << ':' << fpos.column
                   << ": error: "
                   << vrml97_parse_error_msg(err.descriptor) << endl;

        return error_status<>(error_status<>::fail);
    }

private:

    std::ostringstream* errorString;
};

#endif	/* _VRMLPARSERSTRUCTS_H */

