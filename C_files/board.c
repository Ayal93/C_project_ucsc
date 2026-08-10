#include <stdio.h>

#include "type.h"


           // board squars-----------------

    Square squares[40] = {
    
  
    {Start,  {None,  0, 0,   0,  0,  0, -1, 0, 0, 0}, "GO"},
    {Property, {Brown,  1500,  750,  150, 500, 2000, -1, 0, 0, 0}, "Pettah"},
    {Event,   {None,    0,  0,    0,   0,     0, -1, 0, 0, 0}, "Community Development Fund"},
    {Property, {Brown,  1500,   750,  150,  500,  2000, -1, 0, 0, 0}, "Maradana"},
    {Tax,      {None,      0,     0,    0,    0,     0, -1, 0, 0, 0}, "Income Tax"},
    {Railway,  {None,  2000,  1000,  200,    0,     0, -1, 0, 0, 0}, "Colombo Fort Railway Station"},
    {Property,  {LightBlue, 2500, 1250, 250,  750,  3000, -1, 0, 0, 0}, "Bambalapitiya"},
    {Event,    {None,      0,     0,    0,    0,     0, -1, 0, 0, 0}, "National Event Card"},
    {Property, {LightBlue, 2500, 1250, 250,  750,  3000, -1, 0, 0, 0}, "Wellawatte"},
    {Property, {LightBlue, 2500, 1250, 250,  750,  3000, -1, 0, 0, 0}, "Mount Lavinia"},
    {Special,  {None,     0,     0,    0,    0,     0, -1, 0, 0, 0}, "Jail / Just Visiting"},
    {Property, {Pink,  3500, 1750,  350, 1000,  4000, -1, 0, 0, 0}, "Nugegoda"},
    {Utility,  {None, 1500,  750,  150,    0,     0, -1, 0, 0, 0}, "Ceylon Electricity Board"},
    {Property,  {Pink,   3500, 1750,  350, 1000,  4000, -1, 0, 0, 0}, "Maharagama"},
    {Property,  {Pink,   3500,   1750,  350, 1000,  4000, -1, 0, 0, 0}, "Kottawa"},
    {Railway,   {None,  2000, 1000,  200,    0,     0, -1, 0, 0, 0}, "Kandy Railway Station"},
    {Property,  {Orange, 4500, 2250,  450, 1250,  5000, -1, 0, 0, 0}, "Negombo"},
    {Insurance, {None,      0,   0,  0,   0,  0, -1, 0, 0, 0}, "Sri Lanka Insurance"},
    {Property,  {Orange, 4500,  2250, 450, 1250,  5000, -1, 0, 0, 0}, "Katunayake"},
    {Property,  {Orange, 4500,  2250, 450, 1250,  5000, -1, 0, 0, 0}, "Ja-Ela"},
    {Special,   {None,  0,  0,  0,   0,0, -1, 0, 0, 0}, "Free Parking"},
    {Property,  {Red,    5500,  2750,  550, 1500,  6000, -1, 0, 0, 0}, "Kandy City"},
    {Event,     {None,    0,  0,   0,   0,     0, -1, 0, 0, 0}, "National Event Card"},
    {Property,  {Red,    5500,  2750,  550, 1500,  6000, -1, 0, 0, 0}, "Peradeniya"},
    {Property,  {Red,    5500,  2750,  550, 1500,  6000, -1, 0, 0, 0}, "Katugastota"},
    {Railway,   {None,  2000,  1000,  200,    0,     0, -1, 0, 0, 0}, "Galle Railway Station"},
    {Property,  {Yellow, 6500,  3250,  650, 2000,  8000, -1, 0, 0, 0}, "Galle Fort"},
    {Property,  {Yellow, 6500,  3250,  650, 2000,  8000, -1, 0, 0, 0}, "Unawatuna"},
    {Utility,   {None,  1500,   750,  150,    0,     0, -1, 0, 0, 0}, "National Water Supply Board"},
    {Property,  {Yellow, 6500,  3250,  650, 2000,  8000, -1, 0, 0, 0}, "Hikkaduwa"},
    {Special,   {None,      0,     0,    0,    0,     0, -1, 0, 0, 0}, "Go To Jail"},
    {Property,  {Green,  8000,  4000,  800, 2500, 10000, -1, 0, 0, 0}, "Jaffna Town"},
    {Property,  {Green,  8000,  4000,  800, 2500, 10000, -1, 0, 0, 0}, "Nallur"},
    {Insurance, {None,      0,     0,    0,    0,     0, -1, 0, 0, 0}, "Ceylinco Insurance"},
    {Property,  {Green,  8000,  4000,  800, 2500, 10000, -1, 0, 0, 0}, "Trincomalee"},
    {Railway,   {None,  2000,  1000,  200,    0,     0, -1, 0, 0, 0}, "Jaffna Railway Station"},
    {Event,     {None,      0,     0,    0,    0,     0, -1, 0, 0, 0}, "National Event Card"},
    {Property,  {DarkBlue, 10000, 5000, 1000, 3000, 12000, -1, 0, 0, 0}, "Nuwara Eliya"},
    {Bank,      {None,      0,     0,    0,    0,     0, -1, 0, 0, 0}, "Bank of Ceylon"},
    {Property,  {DarkBlue, 10000, 5000, 1000, 3000, 12000, -1, 0, 0, 0}, "Galle Face"}
};

    

//-------------------------------------------------------------------------

