#pragma once
#ifndef JMD_UTILS_OBJECT_H_
#define JMD_UTILS_OBJECT_H_

/*
 //====================================================================//
 
 ==========================
 Joseph DeGol
 UIUC Fall 2013
 ==========================
 JMD_Utils_Object: Version 1.0
 ==========================
 
 ================================================================
 JMD_Utils_Object.hpp
 A class for type-hiding, i.e. an "any" class like boost::any
 ================================================================
 
 List of Functions:
 
 ----- Enumerations -----
 --- End Enumerations ---
 
 ----- Constructors -----
 
 Options();
 
 --- end Constructors ---
 
 ----- Option Methods -----
 
 --- end Option Methods ---
 
 //====================================================================//
 */
 




//====================================================================//
//====================================================================//
//============================ Preamble ==============================//
//====================================================================//
//====================================================================//


//---------------------------------------------------------------//
//------------------------- Includes ----------------------------//
//---------------------------------------------------------------//

#include <iostream>
#include <utility>

//---------------------------------------------------------------//
//------------------------ end Includes -------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//----------------------- Namespaces ----------------------------//
//---------------------------------------------------------------//

//---------------------------------------------------------------//
//---------------------- end Namespaces -------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//------------------------- Globals -----------------------------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------------------------ end Globals --------------------------//
//---------------------------------------------------------------//


//---------------------------------------------------------------//
//------------------- Function Prototypes -----------------------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------------------ end Function Prototypes --------------------//
//---------------------------------------------------------------//

//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//
//====================================================================//





namespace JMD
{

	class JMD_Utils_Object;
	template <class T> T Get_Value(JMD_Utils_Object& obj_param);

	//====================================================================//
    //====================================================================//
    //========================= Helper Objects ===========================//
    //====================================================================//
    //====================================================================//
    
    //---------------------------------------------------------------//
    //--------------------- JMD Base Object -------------------------//
    //---------------------------------------------------------------//
	class JMD_Base
	{
		public:
		virtual ~JMD_Base() { }
		virtual JMD_Base* clone() const = 0;
	};
	//---------------------------------------------------------------//
    //------------------- End JMD Base Object -----------------------//
    //---------------------------------------------------------------//
 
 
 	//---------------------------------------------------------------//
    //--------------------- JMD Type Object -------------------------//
    //---------------------------------------------------------------//
	template <class T> class JMD_Type : public JMD_Base
	{
		T t;
	 
		public:
		JMD_Type(const T& t_) : t(t_) { }
		JMD_Base* clone() const
		{
			return new JMD_Type(t);
		}
		friend T Get_Value<>(JMD_Utils_Object& obj_param);
	};
	//---------------------------------------------------------------//
    //------------------- End JMD Type Object -----------------------//
    //---------------------------------------------------------------//
        
        
	//---------------------------------------------------------------//
    //--------------------- JMD Type Object -------------------------//
    //---------------------------------------------------------------//
    class JMD_Object_Bad_Get_Value : public std::exception
	{
		public:
		const char* what() const throw()
		{
			return "Bad JMD_Utils_Object Get_Value() exception";
		}
	};
	//---------------------------------------------------------------//
    //--------------------- JMD Type Object -------------------------//
    //---------------------------------------------------------------//
    
    //====================================================================//
    //====================================================================//
    //========================= Helper Objects ===========================//
    //====================================================================//
    //====================================================================//



	//====================================================================//
    //====================================================================//
    //=================== JMD Utils Object Definition ====================//
    //====================================================================//
    //====================================================================//
	class JMD_Utils_Object
	{
		//---------------------------------------------------------------//
        //------------------------- Private -----------------------------//
        //---------------------------------------------------------------//
        
        /*----- Variables -----*/
		JMD_Base* Value;
		/*--- End Variables ---*/
	 
	 	//---------------------------------------------------------------//
        //----------------------- end Private ---------------------------//
        //---------------------------------------------------------------//
        
        
        //---------------------------------------------------------------//
        //-------------------------- Public -----------------------------//
        //---------------------------------------------------------------//
		public:
		
		/*----- Constructors -----*/
		JMD_Utils_Object();
	 
		JMD_Utils_Object(JMD_Utils_Object const & obj_param);
		
		template <class value_param> JMD_Utils_Object(const value_param& v_) : Value(new JMD_Type<value_param>(v_)) {}
 		/*--- End Constructors ---*/
 		
 		/*----- Destructors -----*/
 		~JMD_Utils_Object();
 		/*--- End Destructors ---*/
 		
 		/*----- Operator Overloads -----*/
		JMD_Utils_Object& operator=(const JMD_Utils_Object& obj_param);
		/*--- End Operator Overloads ---*/
		
		/*----- Methods -----*/
		void swap(JMD_Utils_Object& obj_param);
		
		template <class T> friend T Get_Value(JMD_Utils_Object& obj_param)
		//template <class T> T any_cast(any& a)
		{
			JMD_Type<T>* Value = dynamic_cast<JMD_Type<T>*>(obj_param.Value);
			if(Value == 0)
			{
				throw JMD_Object_Bad_Get_Value();
			}
			else
			{
				return Value->t;
			}
		}
		/*--- End Methods ---*/

		//---------------------------------------------------------------//
        //------------------------ end Public ---------------------------//
        //---------------------------------------------------------------//
        
	};
	//====================================================================//
    //====================================================================//
    //====================================================================//
    //====================================================================//
    //====================================================================//

}
#endif