#include "DetectorConstruction.hh"

#include "DetectorMessenger.hh"

#include "G4Material.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"

#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4AssemblyVolume.hh"
#include "G4VSolid.hh"
#include "G4Trap.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "DetectionSystemNew.hh"

#include <math.h>


////////////////////////////////////////////////
// building and placing the different parts   //
// of the  chamber 		          //
// including chamber itself, magnets and      //
// mounts for magnets and detectors           //
// not including detectors                    //
////////////////////////////////////////////////


DetectionSystemNew::DetectionSystemNew()
{

    this->NUMBER_OF_MAGNETS  = 8;
    
    ///////////////////////////////////////////////////////////////////////////
    // Assigning materials used to their relevant parts inside the detector  //
    ///////////////////////////////////////////////////////////////////////////

    this->chamber_material = "Delrin";
//    this->cold_finger_material = "Copper";
    this->magnet_material = "NdFeB"; 
    this->photon_shield_layer_one_material  = "WTa" ;  //NEED TO CHANGE
    this->photon_shield_layer_two_material  = "Tin" ;  //NEED TO CHANGE
    this->photon_shield_layer_three_material  = "Aluminum" ;  //NEED TO CHANGE
 //   this->bias_plate_material = "Aluminum";
//    this->shield_cover_material = "Delrin";
    this->magnet_cover_material = "Delrin";
//    this->




    ////////////////////////////////////////////////////////
    // Defining the dimensions of the detector components //
    ////////////////////////////////////////////////////////

    //////////////////////////////////
    // Chamber Hemisphere Component //
    //////////////////////////////////

    this->chamber_hemisphere_inner_radius = 100.00*mm;
    this->chamber_hemisphere_outer_radius = 110.00*mm;

    //////////////////////////////////////////
    // Chamber Cylinder/Beam Pipe Component //
    //////////////////////////////////////////

    this->chamber_cylinder_inner_radius = 0*mm;
    this->chamber_cylinder_outer_radius = 40*mm;
    this->chamber_cylinder_height = 100*mm;

    //////////////////////////////
    // Chamber Cut Out Cylinder //
    //////////////////////////////

    this->chamber_cut_out_inner_radius = 0*mm;
    this->chamber_cut_out_outer_radius = 35*mm;
    this->chamber_cut_out_height = 200*mm;


    /////////////
    // Magnets //
    /////////////

    this->plate_one_one_thickness = 3*mm;
    this->plate_one_one_length = 62*mm;  //SPICE = 75*mm;
    this->plate_one_one_height = 30*mm; // z-component
    this->plate_one_one_lower_height = 20*mm;

    this->plate_one_two_thickness = 5*mm;
    this->plate_one_two_length = 30*mm; //SPICE =  55*mm;
    this->plate_one_two_height = 30*mm;


    this->plate_two_one_thickness = 3*mm;
    this->plate_two_one_length = 52*mm;  //SPICE = 75*mm;
    this->plate_two_one_height = 20*mm; // z-component

    this->plate_two_two_thickness = 5*mm;
    this->plate_two_two_length = 20*mm; //SPICE =  55*mm;
    this->plate_two_two_height = 20*mm;


    this->plate_three_one_thickness = 3*mm;
    this->plate_three_one_length = 42*mm;  //SPICE = 75*mm;
    this->plate_three_one_height = 10*mm; // z-component

    this->plate_three_two_thickness = 5*mm;
    this->plate_three_two_length = 10*mm; //SPICE =  55*mm;
    this->plate_three_two_height = 10*mm;


    this->cutting_box_angle = 90*deg;
    this->distance_from_target = 0*mm; // in z-direction
    this->plate_one_edge_x = (93*mm - this->plate_one_one_length); // 92mm is radius of chamber
	this->no_magnet_layer = 3;

	///////////////////
	// Magnet Covers //
	///////////////////

	this->magnet_cover_thickness =2*mm;	


    //////////////////////
    // Photon Shielding //
    //////////////////////  

    this->photon_shield_layer_one_thickness = (25)*mm;
    this->photon_shield_layer_two_thickness = (4)*mm;
    this->photon_shield_layer_three_thickness = (1)*mm;
    this->photon_shield_target_distance = (25)*mm;
	this->detector_full_width = (89)*mm;
	this->detector_target_distance = (75)*mm;

    ///////////////////////////////////
    // Photon Shielding Beam Cut Out //
    ///////////////////////////////////

    this->photon_shield_beam_cut_outer_radius = (5)*mm;
    this->photon_shield_beam_cut_inner_radius = (0)*mm;
    this->photon_shield_beam_cut_height = (100)*mm;


    ////////////////////////
    // Cold Finger Piping //
    ////////////////////////    

//    this->cold_finger_inner_radius = (15)*mm;
//    this->cold_finger_thickness = (3)*mm;
//    this->cold_finger_height = (100)*mm;

    ///////////////////////////////////////////////////////
    // Defining the positions of the detector components //
    ///////////////////////////////////////////////////////

//    this->chamber_hemisphere_dist = (0.)*mm;
//    this->chamber_cylinder_dist = (-75.)*mm;
//    this->cold_finger_dist = (-75)*mm;


}   //end NewDetectionSystem

DetectionSystemNew::~DetectionSystemNew()
{


    ///////////////////////////////////////////////////////////
    // Deleting the logical space of the detector components //
    ///////////////////////////////////////////////////////////


//    delete chamber_log;
    delete final_chamber_log;
//    delete cold_finger_log;
    delete magnet_log;
    delete photon_shield_layer_one_log;
    delete photon_shield_layer_two_log;
    delete photon_shield_layer_three_log;
//    delete bias_plate_log;
//    delete shield_cover_log;
//    delete magnet_cover_log;

    ////////////////////////////////////////////////////////////
    // Deleting the physical space of the detector components //
    ////////////////////////////////////////////////////////////

//    delete chamber_phys;
    delete final_chamber_phys;
//    delete cold_finger_phys;
    delete magnet_phys;
    delete photon_shield_layer_one_phys;
	delete photon_shield_layer_two_phys;
    delete photon_shield_layer_three_phys;
//    delete bias_plate_phys;
//    delete shield_cover_phys;
//    delete magnet_cover_phys;

}   //end ~NewDetectionSystem

    ////////////////////////////////////////////////////////
    // Need to now build and place components of detector //
    ////////////////////////////////////////////////////////

void DetectionSystemNew::Build(G4LogicalVolume* exp_hall_log)
{
  this->expHallLog = exp_hall_log;
    ///////////////////////////////////////////////////
    // Building functions for components of detector //
    ///////////////////////////////////////////////////

    BuildChamber();
//    BuildColdFinder();
    BuildMagnet();
    BuildPhotonShield();
///    BuildBiasPlate();
//    BuildShieldCover();
//    BuildMagnetCover();

    //////////////////////////////////////////////////
    // Placing functions for components of detector //
    //////////////////////////////////////////////////

    PlaceChamber();
 //   PlaceColdFinger();
    PlacePhotonShield();
//    PlaceBiasPlate();  
//    PlaceShieldCover();
    
    for(G4int copyID=0; copyID<this->NUMBER_OF_MAGNETS; copyID++)
    {
        PlaceMagnet(copyID);
//        PlaceMagnetCover(copyID);
    }

} //End Build


/////////////////////////////////
// Building components methods //
/////////////////////////////////

////////////////////
// Target Chamber //
////////////////////



void DetectionSystemNew::BuildChamber()
{
    ////////////////////////////////
    // Visualisation of Component //
    ////////////////////////////////

    G4VisAttributes* vis_att = new G4VisAttributes(G4Colour(CHAMBER_COL));
    vis_att->SetVisibility(true);

    /////////////////////////////
    // Dimensions of Component //
    /////////////////////////////


    //Main hemisphere shell
    G4double hemisphere_inner_radius = this->chamber_hemisphere_inner_radius;
    G4double hemisphere_outer_radius = this->chamber_hemisphere_outer_radius;

    //Main Cylinder
    G4double cylinder_inner_radius = this->chamber_cylinder_inner_radius;
    G4double cylinder_outer_radius = this->chamber_cylinder_outer_radius;
    G4double cylinder_height = this->chamber_cylinder_height/2;

    //Cut Out Cylinder
    G4double cut_out_inner_radius = this->chamber_cut_out_inner_radius;
    G4double cut_out_outer_radius = this->chamber_cut_out_outer_radius;
    G4double cut_out_height = this->chamber_cut_out_height;

    //Primitive Volumes
    G4Sphere* chamber_hemisphere = new G4Sphere("chamber_hemisphere", hemisphere_inner_radius, hemisphere_outer_radius, 0*pi, 2*pi, 90*deg,90*deg);
    G4Tubs* chamber_cylinder = new G4Tubs("chamber_cylinder", cylinder_inner_radius, cylinder_outer_radius, cylinder_height, 0*deg, 360*deg);
    G4Tubs* chamber_cut_out = new G4Tubs("chamber_cut_out", cut_out_inner_radius, cut_out_outer_radius, cut_out_height, 0*deg, 360*deg);

    //Putting Chamber components together
    G4ThreeVector zTrans(0,0,-((cylinder_height*2)+40*mm));
    G4UnionSolid* chamber_solid = new G4UnionSolid("chamber_solid", chamber_hemisphere, chamber_cylinder,0,zTrans);
    G4SubtractionSolid* final_chamber = new G4SubtractionSolid("final_chamber", chamber_solid, chamber_cut_out);

    //Logical Volume
    G4Material* chamber_material = G4Material::GetMaterial(this->chamber_material);
    final_chamber_log = new G4LogicalVolume(final_chamber,chamber_material,"final_chamber_log",0,0,0);
    final_chamber_log->SetVisAttributes(vis_att);



} //end of additions




///////////////////////
// A Singular Magnet //
///////////////////////



void DetectionSystemNew::BuildMagnet()
{

    //Visualisation
    G4VisAttributes* vis_att = new G4VisAttributes(G4Colour(NDFEB_COL));
    vis_att->SetVisibility(true);

    //Build layer one Plate One
    G4Box* plate_one_one_pre_cut = new G4Box("plate_one_one_pre_cut", this->plate_one_one_length/2., this->plate_one_one_thickness/2., this->plate_one_one_height/2.);
    G4Box* plate_one_one_cut_box = new G4Box("plate_one_one_cut_box", this->plate_one_one_length/2., this->plate_one_one_thickness/2. + 1., this->plate_one_one_height/2.);
    
    // ( Cut box is rotated and moved, exact movement calculated below )
    G4double angle_to_corner = atan(this->plate_one_one_length/this->plate_one_one_height);
    G4double hypotenuse_to_corner = sqrt(pow(this->plate_one_one_height/2., 2) + pow(this->plate_one_one_length/2., 2));
    G4double angle_difference, translate_cut_x, translate_cut_z;

    if (angle_to_corner < this->cutting_box_angle)
    {
        angle_difference = this->cutting_box_angle - angle_to_corner;
        translate_cut_x = (hypotenuse_to_corner * sin(angle_difference)) + this->plate_one_one_length/2.;
        translate_cut_z = (hypotenuse_to_corner * cos(angle_difference)) - this->plate_one_one_height/2. + this->plate_one_one_lower_height;
    }

    else if (angle_to_corner > this->cutting_box_angle)
    {
        angle_difference = angle_to_corner - this->cutting_box_angle;
        translate_cut_x = this->plate_one_one_length/2. - (hypotenuse_to_corner * sin(angle_difference));
        translate_cut_z = (hypotenuse_to_corner * cos(angle_difference)) - this->plate_one_one_height/2. + this->plate_one_one_lower_height;
    }

    G4ThreeVector translate_cut_box(-translate_cut_x, 0, translate_cut_z);
    G4RotationMatrix* rotate_cut_box = new G4RotationMatrix;
    rotate_cut_box->rotateY(this->cutting_box_angle);
    G4SubtractionSolid* plate_one_one = new G4SubtractionSolid("plate_one_one", plate_one_one_pre_cut, plate_one_one_cut_box,
    rotate_cut_box, translate_cut_box);
/*
    //Build layer one Plate Two
    G4Box* plate_one_two = new G4Box("plate_one_two", this->plate_one_two_length/2., (this->plate_one_two_thickness + this->plate_one_one_thickness/2.), this->plate_one_two_height/2.);
    
    //Combine layer one Plates
    G4ThreeVector translate_plate_one_two(this->plate_one_one_length/2. - this->plate_one_two_length/2., 0, 0);
    G4UnionSolid* layer_one_combo = new G4UnionSolid("layer_one_combo", plate_one_one, plate_one_two, 0, translate_plate_one_two);
*/
	//Build layer two
    G4Box* plate_two_one = new G4Box("plate_two_one", this->plate_two_one_length/2., this->plate_two_one_thickness/2., this->plate_two_one_height/2.);
/*    G4Box* plate_two_two = new G4Box("plate_two_two", this->plate_two_two_length/2., (this->plate_two_two_thickness + this->plate_two_one_thickness/2.), this->plate_two_two_height/2.);

	//Combine Layer two
    G4ThreeVector translate_plate_two_two(this->plate_two_one_length/2. - this->plate_two_two_length/2., 0, 0);
    G4UnionSolid* layer_two_combo = new G4UnionSolid("layer_two_combo", plate_two_one, plate_two_two, 0, translate_plate_two_two);
*/
	//Build layer three
    G4Box* plate_three_one = new G4Box("plate_three_one", this->plate_three_one_length/2., this->plate_three_one_thickness/2., this->plate_three_one_height/2.);
/*    G4Box* plate_three_two = new G4Box("plate_three_two", this->plate_three_two_length/2., (this->plate_three_two_thickness + this->plate_three_one_thickness/2.), this->plate_three_two_height/2.);

	//Combine layer three
    G4ThreeVector translate_plate_three_two(this->plate_three_one_length/2. - this->plate_three_two_length/2., 0, 0);
    G4UnionSolid* layer_three_combo = new G4UnionSolid("layer_three_combo", plate_three_one, plate_three_two, 0, translate_plate_three_two);
*/
	
	//Combine all three layers
    G4ThreeVector translate_layer_two(-((this->plate_one_one_length/2)-(this->plate_two_one_length/2)), 0, -(this->plate_one_one_height-this->plate_two_one_height/4));
    G4UnionSolid* layers_two = new G4UnionSolid("layers_two", plate_one_one/*layer_one_combo*/, plate_two_one /*layer_two_combo*/, 0, translate_layer_two);

    G4ThreeVector translate_layer_three(-((this->plate_one_one_length/2)-(this->plate_three_one_length/2)), 0, -(this->plate_one_one_height+this->plate_two_one_height/2));
    G4UnionSolid* fullmagnet = new G4UnionSolid("fullmagnet", layers_two,plate_three_one  /*layer_three_combo*/, 0,translate_layer_three);


    //Logical Volume
    G4Material* magnet_material = G4Material::GetMaterial(this->magnet_material);
    magnet_log = new G4LogicalVolume(fullmagnet, magnet_material, "magnet_log", 0, 0, 0);
    magnet_log->SetVisAttributes(vis_att);


} // end:BuildCollectorMagnet()



//////////////////
// Magnet Cover //
/////////////////


/*
void DetectionSystemNew::BuildMagnetCover()
{

    //Visualisation
    G4VisAttributes* vis_att = new G4VisAttributes(G4Colour(MAGCOV_COL));
    vis_att->SetVisibility(true);

    //Build layer one Plate One
    G4Box* plate_one_one_pre_cut = new G4Box("plate_one_one_pre_cut", this->plate_one_one_length/2.+this->magnet_cover_thickness, this->plate_one_one_thickness/2.+this->magnet_cover_thickness, this->plate_one_one_height/2.+this->magnet_cover_thickness);
    G4Box* plate_one_one_cut_box = new G4Box("plate_one_one_cut_box", this->plate_one_one_length/2.+this->magnet_cover_thickness, this->plate_one_one_thickness/2. + 1.+this->magnet_cover_thickness, this->plate_one_one_height/2.+this->magnet_cover_thickness);
    
    // ( Cut box is rotated and moved, exact movement calculated below )
    G4double angle_to_corner = atan((this->plate_one_one_length+this->magnet_cover_thickness)/(this->plate_one_one_height+this->magnet_cover_thickness));
    G4double hypotenuse_to_corner = sqrt(pow(this->plate_one_one_height/2.+this->magnet_cover_thickness, 2) + pow(this->plate_one_one_length/2.+this->magnet_cover_thickness, 2));
    G4double angle_difference, translate_cut_x, translate_cut_z;

    if (angle_to_corner < this->cutting_box_angle)
    {
        angle_difference = this->cutting_box_angle - angle_to_corner;
        translate_cut_x = (hypotenuse_to_corner * sin(angle_difference)) + this->plate_one_one_length/2.+this->magnet_cover_thickness;
        translate_cut_z = (hypotenuse_to_corner * cos(angle_difference)) - this->plate_one_one_height/2.-this->magnet_cover_thickness + this->plate_one_one_lower_height;
    }

    else if (angle_to_corner > this->cutting_box_angle)
    {
        angle_difference = angle_to_corner - this->cutting_box_angle;
        translate_cut_x = this->plate_one_one_length/2.+this->magnet_cover_thickness - (hypotenuse_to_corner * sin(angle_difference));
        translate_cut_z = (hypotenuse_to_corner * cos(angle_difference)) - this->plate_one_one_height/2.-this->magnet_cover_thickness + this->plate_one_one_lower_height;
    }

    G4ThreeVector translate_cut_box(-translate_cut_x, 0, translate_cut_z);
    G4RotationMatrix* rotate_cut_box = new G4RotationMatrix;
    rotate_cut_box->rotateY(this->cutting_box_angle);
    G4SubtractionSolid* plate_one_one = new G4SubtractionSolid("plate_one_one", plate_one_one_pre_cut, plate_one_one_cut_box,
    rotate_cut_box, translate_cut_box);

    //Build layer one Plate Two
    G4Box* plate_one_two = new G4Box("plate_one_two", this->plate_one_two_length/2.+this->magnet_cover_thickness, (this->plate_one_two_thickness + this->plate_one_one_thickness/2.+this->magnet_cover_thickness), this->plate_one_two_height/2.+this->magnet_cover_thickness);
    
    //Combine layer one Plates
    G4ThreeVector translate_plate_one_two(this->plate_one_one_length/2. - this->plate_one_two_length/2., 0, 0);
    G4UnionSolid* layer_one_combo = new G4UnionSolid("layer_one_combo", plate_one_one, plate_one_two, 0, translate_plate_one_two);

	//Build layer two
    G4Box* plate_two_one = new G4Box("plate_two_one", this->plate_two_one_length/2.+this->magnet_cover_thickness, this->plate_two_one_thickness/2.+this->magnet_cover_thickness, this->plate_two_one_height/2.+this->magnet_cover_thickness/2);
    G4Box* plate_two_two = new G4Box("plate_two_two", this->plate_two_two_length/2.+this->magnet_cover_thickness, (this->plate_two_two_thickness + this->plate_two_one_thickness/2.+this->magnet_cover_thickness), this->plate_two_two_height/2.+this->magnet_cover_thickness/2);

	//Combine Layer two
    G4ThreeVector translate_plate_two_two(this->plate_two_one_length/2. - this->plate_two_two_length/2., 0, 0);
    G4UnionSolid* layer_two_combo = new G4UnionSolid("layer_two_combo", plate_two_one, plate_two_two, 0, translate_plate_two_two);

	//Build layer three
    G4Box* plate_three_one = new G4Box("plate_three_one", this->plate_three_one_length/2.+this->magnet_cover_thickness, this->plate_three_one_thickness/2.+this->magnet_cover_thickness, this->plate_three_one_height/2.+this->magnet_cover_thickness);
    G4Box* plate_three_two = new G4Box("plate_three_two", this->plate_three_two_length/2.+this->magnet_cover_thickness, (this->plate_three_two_thickness + this->plate_three_one_thickness/2.+this->magnet_cover_thickness), this->plate_three_two_height/2.+this->magnet_cover_thickness);

	//Combine layer three
    G4ThreeVector translate_plate_three_two(this->plate_three_one_length/2. - this->plate_three_two_length/2., 0, 0);
    G4UnionSolid* layer_three_combo = new G4UnionSolid("layer_three_combo", plate_three_one, plate_three_two, 0, translate_plate_three_two);

	
	//Combine all three layers
    G4ThreeVector translate_layer_two(-((this->plate_one_one_length/2)-(this->plate_two_one_length/2)), 0, -(this->plate_one_one_height-this->plate_two_one_height/4+this->magnet_cover_thickness*2));
    G4UnionSolid* layers_two = new G4UnionSolid("layers_two", layer_one_combo, layer_two_combo, 0, translate_layer_two);

    G4ThreeVector translate_layer_three(-((this->plate_one_one_length/2)-(this->plate_three_one_length/2)), 0, -(this->plate_one_one_height+this->plate_two_one_height/2));
    G4UnionSolid* magnetcoversolid = new G4UnionSolid("magnetcoversolid", layers_two,layer_three_combo, 0,translate_layer_three);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////				RE-BUILD MAGNETS			////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Build layer one Plate One
    G4Box* magnet_plate_one_one_pre_cut = new G4Box("magnet_plate_one_one_pre_cut", this->plate_one_one_length/2., this->plate_one_one_thickness/2., this->plate_one_one_height/2.);
    G4Box* magnet_plate_one_one_cut_box = new G4Box("magnet_plate_one_one_cut_box", this->plate_one_one_length/2., this->plate_one_one_thickness/2. + 1., this->plate_one_one_height/2.);
    
    // ( Cut box is rotated and moved, exact movement calculated below )
    G4double magnet_angle_to_corner = atan(this->plate_one_one_length/this->plate_one_one_height);
    G4double magnet_hypotenuse_to_corner = sqrt(pow(this->plate_one_one_height/2., 2) + pow(this->plate_one_one_length/2., 2));
    G4double magnet_angle_difference, magnet_translate_cut_x, magnet_translate_cut_z;

    if (magnet_angle_to_corner < this->cutting_box_angle)
    {
        magnet_angle_difference = this->cutting_box_angle - angle_to_corner;
        magnet_translate_cut_x = (magnet_hypotenuse_to_corner * sin(magnet_angle_difference)) + this->plate_one_one_length/2.;
        magnet_translate_cut_z = (magnet_hypotenuse_to_corner * cos(magnet_angle_difference)) - this->plate_one_one_height/2. + this->plate_one_one_lower_height;
    }

    else if (magnet_angle_to_corner > this->cutting_box_angle)
    {
        magnet_angle_difference = magnet_angle_to_corner - this->cutting_box_angle;
        magnet_translate_cut_x = this->plate_one_one_length/2. - (magnet_hypotenuse_to_corner * sin(magnet_angle_difference));
        magnet_translate_cut_z = (magnet_hypotenuse_to_corner * cos(magnet_angle_difference)) - this->plate_one_one_height/2. + this->plate_one_one_lower_height;
    }

    G4ThreeVector magnet_translate_cut_box(-magnet_translate_cut_x, 0, magnet_translate_cut_z);
    G4RotationMatrix* magnet_rotate_cut_box = new G4RotationMatrix;
    magnet_rotate_cut_box->rotateY(this->cutting_box_angle);
    G4SubtractionSolid* magnet_plate_one_one = new G4SubtractionSolid("magnet_plate_one_one", magnet_plate_one_one_pre_cut, magnet_plate_one_one_cut_box,
    magnet_rotate_cut_box, magnet_translate_cut_box);

    //Build layer one Plate Two
    G4Box* magnet_plate_one_two = new G4Box("magnet_plate_one_two", this->plate_one_two_length/2., (this->plate_one_two_thickness + this->plate_one_one_thickness/2.), this->plate_one_two_height/2.);
    
    //Combine layer one Plates
    G4ThreeVector magnet_translate_plate_one_two(this->plate_one_one_length/2. - this->plate_one_two_length/2., 0, 0);
    G4UnionSolid* magnet_layer_one_combo = new G4UnionSolid("magnet_layer_one_combo", magnet_plate_one_one, magnet_plate_one_two, 0, magnet_translate_plate_one_two);

	//Build layer two
    G4Box* magnet_plate_two_one = new G4Box("magnet_plate_two_one", this->plate_two_one_length/2., this->plate_two_one_thickness/2., this->plate_two_one_height/2.);
    G4Box* magnet_plate_two_two = new G4Box("magnet_plate_two_two", this->plate_two_two_length/2., (this->plate_two_two_thickness + this->plate_two_one_thickness/2.), this->plate_two_two_height/2.);

	//Combine Layer two
    G4ThreeVector magnet_translate_plate_two_two(this->plate_two_one_length/2. - this->plate_two_two_length/2., 0, 0);
    G4UnionSolid* magnet_layer_two_combo = new G4UnionSolid("magnet_layer_two_combo", magnet_plate_two_one, magnet_plate_two_two, 0, translate_plate_two_two);

	//Build layer three
    G4Box* magnet_plate_three_one = new G4Box("magnet_plate_three_one", this->plate_three_one_length/2., this->plate_three_one_thickness/2., this->plate_three_one_height/2.);
    G4Box* magnet_plate_three_two = new G4Box("magnet_plate_three_two", this->plate_three_two_length/2., (this->plate_three_two_thickness + this->plate_three_one_thickness/2.), this->plate_three_two_height/2.);

	//Combine layer three
    G4ThreeVector magnet_translate_plate_three_two(this->plate_three_one_length/2. - this->plate_three_two_length/2., 0, 0);
    G4UnionSolid* magnet_layer_three_combo = new G4UnionSolid("magnet_layer_three_combo", magnet_plate_three_one, magnet_plate_three_two, 0, translate_plate_three_two);

	
	//Combine all three layers
    G4ThreeVector magnet_translate_layer_two(-((this->plate_one_one_length/2)-(this->plate_two_one_length/2)), 0, -(this->plate_one_one_height-this->plate_two_one_height/4));
    G4UnionSolid* magnet_layers_two = new G4UnionSolid("magnet_layers_two", magnet_layer_one_combo, magnet_layer_two_combo, 0, magnet_translate_layer_two);

    G4ThreeVector magnet_translate_layer_three(-((this->plate_one_one_length/2)-(this->plate_three_one_length/2)), 0, -(this->plate_one_one_height+this->plate_two_one_height/2));
    G4UnionSolid* fullmagnet = new G4UnionSolid("fullmagnet", magnet_layers_two,magnet_layer_three_combo, 0,magnet_translate_layer_three);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	G4ThreeVector movemagnets(this->magnet_cover_thickness,this->magnet_cover_thickness,this->magnet_cover_thickness);
	G4SubtractionSolid* fullmagnetcover = new G4SubtractionSolid("fullmagnetcover", magnetcoversolid,fullmagnet,0,movemagnets);


    //Logical Volume
    G4Material* magnet_cover_material = G4Material::GetMaterial(this->magnet_cover_material);
    magnet_cover_log = new G4LogicalVolume(layers_two, magnet_cover_material, "magnet_cover_log", 0, 0, 0);
    magnet_cover_log->SetVisAttributes(vis_att);


} // end:BuildCollectorMagnetCover()
*/









///////////////////
// Photon Shield //
///////////////////

void DetectionSystemNew::BuildPhotonShield()
{

    //Visualisation
    G4VisAttributes* vis_att1 = new G4VisAttributes(G4Colour(LAYER1_COL));
    vis_att1->SetVisibility(true);
    G4VisAttributes* vis_att2 = new G4VisAttributes(G4Colour(LAYER2_COL));
    vis_att2->SetVisibility(true);
    G4VisAttributes* vis_att3 = new G4VisAttributes(G4Colour(LAYER3_COL));
    vis_att3->SetVisibility(true);

	//Bring in some dimensions pre set at start of code
	G4double detector_full_width = this->detector_full_width/2;
	G4double target_distance = this->photon_shield_target_distance;
	G4double detector_target_distance = this->detector_target_distance;

	G4double layer_one_thickness = this->photon_shield_layer_one_thickness;
	G4double layer_two_thickness = this->photon_shield_layer_two_thickness;
	G4double layer_three_thickness = this->photon_shield_layer_three_thickness;

    //Cut Out Dimensions
    G4double cut_inner_radius = this->photon_shield_beam_cut_inner_radius;
    G4double cut_outer_radius = this->photon_shield_beam_cut_outer_radius;
    G4double cut_height = this->photon_shield_beam_cut_height;


	//Defining the angle made with the z plane from target edge to detector edge
	G4double phi = atan(((detector_full_width / 2)- cut_outer_radius)/detector_target_distance);

	//Defining the First layer x-y plane dimensions using Phi (Uses trig to add on extra length due to small right angle triangle in trapezium)
	G4double layer_one_face_xy_dimension = (cut_outer_radius + (2 * (tan(phi)*target_distance)));
	G4double layer_one_base_xy_dimension = (layer_one_face_xy_dimension +  (tan(phi)*layer_one_thickness));

	//Defining the Second layer x-y plane dimensions using Phi (Uses trig to add on extra length due to small right angle triangle in trapezium)
	G4double layer_two_face_xy_dimension = layer_one_base_xy_dimension;
	G4double layer_two_base_xy_dimension = (layer_two_face_xy_dimension +  (tan(phi)*layer_two_thickness));

	//Defining the Third layer x-y plane dimensions using Phi (Uses trig to add on extra length due to small right angle triangle in trapezium)
	G4double layer_three_face_xy_dimension = layer_two_base_xy_dimension;
	G4double layer_three_base_xy_dimension = (layer_three_face_xy_dimension +  (tan(phi)*layer_three_thickness));

    //Trapezium Dimensions
    //G4double base_width = this->photon_shield_base_width/2;
    //G4double base_length = this->photon_shield_base_length/2;
    //G4double peak_width = this->photon_shield_peak_width/2;
   // G4double peak_length = this->photon_shield_peak_length/2;
    //G4double height = this->photon_shield_height/2;


    //Primitive Volumes
    G4Trd* photon_shield_layer_one_pre = new G4Trd("photon_shield_layer_one_pre", layer_one_base_xy_dimension,  layer_one_face_xy_dimension, layer_one_base_xy_dimension, layer_one_face_xy_dimension, (layer_one_thickness/2));
	    G4Trd* photon_shield_layer_two_pre = new G4Trd("photon_shield_layer_two_pre", layer_two_base_xy_dimension,  layer_two_face_xy_dimension, layer_two_base_xy_dimension, layer_two_face_xy_dimension, (layer_two_thickness/2));
    G4Trd* photon_shield_layer_three_pre = new G4Trd("photon_shield_layer_three_pre", layer_three_base_xy_dimension,  layer_three_face_xy_dimension, layer_three_base_xy_dimension, layer_three_face_xy_dimension, (layer_three_thickness/2));

    G4Tubs* photon_shield_cut_out = new G4Tubs("photon_shield_cut_out", cut_inner_radius, cut_outer_radius, cut_height, 0*deg, 360*deg);

    //Putting Photon Shield components together
    G4SubtractionSolid* photon_shield_layer_one = new G4SubtractionSolid("photon_shield_layer_one", photon_shield_layer_one_pre, photon_shield_cut_out);
    G4SubtractionSolid* photon_shield_layer_two = new G4SubtractionSolid("photon_shield_layer_two", photon_shield_layer_two_pre, photon_shield_cut_out);
    G4SubtractionSolid* photon_shield_layer_three = new G4SubtractionSolid("photon_shield_layer_three", photon_shield_layer_three_pre, photon_shield_cut_out);

    //Logical Volumes
    G4Material* photon_shield_layer_one_material = G4Material::GetMaterial(this->photon_shield_layer_one_material);
    photon_shield_layer_one_log = new G4LogicalVolume(photon_shield_layer_one,photon_shield_layer_one_material,"photon_shield_layer_one_log",0,0,0);
    photon_shield_layer_one_log->SetVisAttributes(vis_att1);

    G4Material* photon_shield_layer_two_material = G4Material::GetMaterial(this->photon_shield_layer_two_material);
    photon_shield_layer_two_log = new G4LogicalVolume(photon_shield_layer_two,photon_shield_layer_two_material,"photon_shield_layer_two_log",0,0,0);
    photon_shield_layer_two_log->SetVisAttributes(vis_att2);

    G4Material* photon_shield_layer_three_material = G4Material::GetMaterial(this->photon_shield_layer_three_material);
    photon_shield_layer_three_log = new G4LogicalVolume(photon_shield_layer_three,photon_shield_layer_three_material,"photon_shield_layer_three_log",0,0,0);
    photon_shield_layer_three_log->SetVisAttributes(vis_att3);

}



/////////////////
// Cold Finger //
/////////////////

//void DetectionSystemNew::BuildColdFinger()
//{

    ////////////////////////////////
    // Visualisation of Component //
    ////////////////////////////////

//    G4VisAttributes* vis_att = new G4VisAttributes(G4Colour(COLD_FINGER_COL));
//    vis_att->SetVisibility(true);


    /////////////////////////////
    // Dimensions of Component //
    /////////////////////////////

    //Main Cylinder
//    G4double inner_radius = this->cold_finger_inner_radius;
//    G4double outer_radius = this->(cold_finger_inner_radius + this->cold_finger_thickness);
//    G4double height = this->cold_finger_height/2;

    //Primitive Volumes
//    G4Tubs* cold_finger = new G4Tubs("cold_finger", inner_radius, outer_radius, height, 0*deg, 360*deg);

    //Logical Volume
//    G4Material* cold_finger_material = G4Material::GetMaterial(this->cold_finger_material);
//    cold_finger_log = new G4LogicalVolume(cold_finger,cold_finger_material,"cold_finger_log",0,0,0);
//    cold_finger_log->SetVisAttributes(vis_att);

//}//end of building cold finger


////////////////////////////////
// Placing components methods //
////////////////////////////////

/////////////
// Chamber //
/////////////


void DetectionSystemNew::PlaceChamber()
{

    G4ThreeVector move(0,0,0);
    final_chamber_phys = new G4PVPlacement(0,move,final_chamber_log, "final_chamber",expHallLog, false,0);

}// end:PlaceChamber

///////////////////
// Photon Shield //
///////////////////

void DetectionSystemNew::PlacePhotonShield()
{

    G4double z_position_layer_one = -this->photon_shield_target_distance;
    G4ThreeVector move1(0,0,z_position_layer_one);
    photon_shield_layer_one_phys = new G4PVPlacement(0,move1,photon_shield_layer_one_log, "photon_shield_layer_one",expHallLog, false,0);

    G4double z_position_layer_two = -(this->photon_shield_target_distance+this->photon_shield_layer_one_thickness/2+(this->photon_shield_layer_two_thickness/2));
    G4ThreeVector move2(0,0,z_position_layer_two);
    photon_shield_layer_two_phys = new G4PVPlacement(0,move2,photon_shield_layer_two_log, "photon_shield_layer_two",expHallLog, false,0);

    G4double z_position_layer_three = -(this->photon_shield_target_distance+this->photon_shield_layer_one_thickness/2+this->photon_shield_layer_two_thickness+(this->photon_shield_layer_three_thickness/2));
    G4ThreeVector move3(0,0,z_position_layer_three);
    photon_shield_layer_three_phys = new G4PVPlacement(0,move3,photon_shield_layer_three_log, "photon_shield_layer_three",expHallLog, false,0);



}// end:PlacePhotonShield

/////////////
// Magnets //
/////////////

void DetectionSystemNew::PlaceMagnet(G4int copyID)
{

  // ** Position Co-ordinates
  G4double magnetPosX = this->plate_one_edge_x + this->plate_one_one_length/2./*+this->magnet_cover_thickness;*/;
  G4double magnetPosZ = -(this->distance_from_target + this->plate_one_one_height/2.); 

  G4RotationMatrix* rotation;
  rotation = RotateMagnets(copyID);
  G4double radial_position = magnetPosX; 
 
  G4ThreeVector move = TranslateMagnets(copyID, radial_position, magnetPosZ);

  // ** Physical Volume
  magnet_phys = new G4PVPlacement(rotation, move, magnet_log,
				  "collector_magnet",expHallLog,
				  false,0);
				  
} // end:PlaceMagnet()


/////////////
// Magnets //
/////////////

void DetectionSystemNew::PlaceMagnetCover(G4int copyID)
{

  // ** Position Co-ordinates
  G4double magnetPosX = this->plate_one_edge_x + this->plate_one_one_length/2. - this->magnet_cover_thickness;
  G4double magnetPosZ = -(this->distance_from_target + this->plate_one_one_height/2.); 

  G4RotationMatrix* rotation;
  rotation = RotateMagnets(copyID);
  G4double radial_position = magnetPosX; 
 
  G4ThreeVector move = TranslateMagnets(copyID, radial_position, magnetPosZ);

  // ** Physical Volume
  magnet_cover_phys = new G4PVPlacement(rotation, move, magnet_cover_log,
				  "collector_magnet_cover",expHallLog,
				  false,0);
				  
} // end:PlaceMagnetCover()





////////////////////////////////////////////////////////////////
// Translations and Rotations of Magnets (same for all parts) //
////////////////////////////////////////////////////////////////

G4RotationMatrix* DetectionSystemNew::RotateMagnets(G4int copyID)
{

  G4RotationMatrix* rotate = new G4RotationMatrix;
  if(this->NUMBER_OF_MAGNETS == 8) 
{
  	/*rotate->rotateZ(-(copyID+0.5)*45.*deg);*/
	if(copyID==0){
  	rotate->rotateZ(350.*deg);}
	else if(copyID==1){
  	rotate->rotateZ(280*deg);}
	else if(copyID==2){
  	rotate->rotateZ(260.*deg);}
	else if(copyID==3){
  	rotate->rotateZ(190.*deg);}
	else if(copyID==4){
  	rotate->rotateZ(170.*deg);}
	else if(copyID==5){
  	rotate->rotateZ(100*deg);}
	else if(copyID==6){
  	rotate->rotateZ(80.*deg);}
	else if(copyID==7){
  	rotate->rotateZ(10.*deg);}
}

  else {
  	/*rotate->rotateZ(-(copyID+0.5)*90.*deg);*/
	if(copyID==0){
  	rotate->rotateZ(330.*deg);}
	else if(copyID==1){
  	rotate->rotateZ(210*deg);}
	else if(copyID==2){
  	rotate->rotateZ(-210.*deg);}
	else if(copyID==3){
  	rotate->rotateZ(30.*deg);}

}

  return rotate;
}

G4ThreeVector DetectionSystemNew::TranslateMagnets(G4int copyID, G4double radial_position, G4double z_position)
{
  G4double x_position(0);
  G4double y_position(0);
  if(this->NUMBER_OF_MAGNETS == 8){
    /*x_position = radial_position*cos((copyID+0.5)*45.*deg);
    y_position = radial_position*sin((copyID+0.5)*45.*deg);*/
	if(copyID==0){
	x_position = radial_position*cos(10.*deg);
    y_position = radial_position*sin(10.*deg);}
	else if(copyID==1){
	x_position = radial_position*cos(80.*deg);
    y_position = radial_position*sin(80.*deg);}
	else if(copyID==2){
	x_position = radial_position*cos(100.*deg);
    y_position = radial_position*sin(100.*deg);}
	else if(copyID==3){
	x_position = radial_position*cos(170.*deg);
    y_position = radial_position*sin(170.*deg);}
	else if(copyID==4){
	x_position = radial_position*cos(190.*deg);
    y_position = radial_position*sin(190.*deg);}
	else if(copyID==5){
	x_position = radial_position*cos(260.*deg);
    y_position = radial_position*sin(260.*deg);}
	else if(copyID==6){
	x_position = radial_position*cos(280.*deg);
    y_position = radial_position*sin(280.*deg);}
	else if(copyID==7){
	x_position = radial_position*cos(-10.*deg);
    y_position = radial_position*sin(-10.*deg);}

  }
  else{
   /* x_position = radial_position*cos((copyID+0.5)*90.*deg);
    y_position = radial_position*sin((copyID+0.5)*90.*deg);*/
	if(copyID==0){
	x_position = radial_position*cos(30.*deg);
    y_position = radial_position*sin(30.*deg);}
	else if(copyID==1){
	x_position = radial_position*cos(150.*deg);
    y_position = radial_position*sin(150.*deg);}
	else if(copyID==2){
	x_position = radial_position*cos(210.*deg);
    y_position = radial_position*sin(210.*deg);}
	else if(copyID==3){
	x_position = radial_position*cos(-30.*deg);
    y_position = radial_position*sin(-30.*deg);}
  }
  return G4ThreeVector(x_position, y_position, z_position);
}
