#ifndef __GriffinDATA__
#define __GriffinDATA__
/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 * Modified by    : Ryan Dunlop  contact address: rdunlop@uoguelph.ca        *
 *---------------------------------------------------------------------------*
 * Decription: This class stores the results of the G4 simulation for the    *
 *             GRIFFIN detector. And was adapted from S1 detector Class.     *
 *             The format is the same as the one which is used for the GANIL *
 *             experiments after conversion of the raw data with GRU.        *
 *             This class derives from TObject (ROOT) and its aim is to be   *
 *             stored in the output TTree of the G4 simulation               *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/


//c++
#include <vector>

//ROOT
#include "TObject.h"
#include "TVector3.h"

class TGriffinData : public TObject {
 private:

        vector<Int_t>   fDetNbr; //clover
        vector<Int_t>   fCrystalNbr; // 0,1,2,3 <=> Blue, Green, Red, White
        vector<TVector3> fPositionFirstHit;
   		vector<Double_t>   fEnergy;
   		
        vector<Double_t> fPrimaryEnergy;
        vector<Int_t>   fPrimaryPdg;

        Int_t fEventNumber;
   
 public:
        TGriffinData();
        virtual ~TGriffinData();

        void   ClearVariables();
        void   Dump() const;



        /////////////////////           GETTERS           ////////////////////////
        Int_t   GetGriffinEDetectorNbr(Int_t i)   {return fDetNbr.at(i);}
        Int_t   GetGriffinEDetectorMult(Int_t)        {return fDetNbr.size();}

        Int_t   GetGriffinECrystalNbr(Int_t i)   {return fCrystalNbr.at(i);}
        Int_t   GetGriffinECrystalMult(Int_t)        {return fCrystalNbr.size();}
 
    	Double_t   GetGriffinEEnergy(Int_t i)     {return fEnergy.at(i);}
                   
        TVector3 GetPositionFirstHit(Int_t i)  {return fPositionFirstHit.at(i);}    
        Int_t GetEventNumber(void)             {return fEventNumber;}

        Double_t GetPrimaryEnergy(Int_t i)    {return fPrimaryEnergy.at(i);}
        Int_t   GetPrimaryPdg(Int_t i)    {return fPrimaryPdg.at(i);}

        /////////////////////           SETTERS           ////////////////////////
        void   SetGriffinEDetectorNbr(Int_t det)  {fDetNbr.push_back(det);}
        void   SetGriffinECrystalNbr(Int_t cry)  {fCrystalNbr.push_back(cry);}
      
        void   SetGriffinEEnergy(Double_t E)  {fEnergy.push_back(E);}  
        void   SetPositionFirstHit(TVector3 position)  {fPositionFirstHit.push_back(position);}
        void   SetEventNumber(Int_t i)          {fEventNumber = i;}

        void   SetPrimaryEnergy(Double_t energy)       {fPrimaryEnergy.push_back(energy);}
        void   SetPrimaryPdg(Int_t pdg)         {fPrimaryPdg.push_back(pdg);}
     
   ClassDef(TGriffinData,1)  // GriffinData structure
};

#endif
        
