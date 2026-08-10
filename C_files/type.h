#ifndef TYPE_H
#define TYPE_H

typedef enum { 
None,   // to identify colour and property group
  Brown,
  LightBlue,
  Pink,
  Orange,
  Red,
  Yellow,
  Green,
  DarkBlue

} PropertyGroup;



typedef enum  {     // to identify the type
    Start,
    Property, 
    Event,
    Tax,
    Special,
    Utility,
    Railway,
    Insurance,
    Bank
}SquareType ;


typedef struct   {    //property values

        
        PropertyGroup group;
        double Purchase_Price;
        double Mortgage_Value;
        double Base_Rental;
        double House_Construction_Cost;
        double Hotel_Construction_Cost;
        int Current_Owner;
        int Mortgage_Status;
        int Insurance_Status;
        int Number_of_buildings;


  }property;

    








typedef struct  {     // declaring a square
    
    SquareType square_type;
    property property;
    char square_name[30];


    } Square;






    

#endif