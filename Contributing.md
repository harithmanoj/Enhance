# Contributing

## Reporting Issues

Bug reports are appreciated But please check if the issue has been reported or if it has been resolved in a release later than the one you use.


## Pull Requests

Your pull requests are welcome; however, they may not be accepted for various reasons. 

For typo corrections, open an issue.

## Documentation 

Doxygen documentation will only be built when code is ready to be released.
Doxygen comment blocks must be in /** ... */

### Files


* \file `[filename]`

* \brief  `[description]`

* Created  date `[dd Month yyyy]`
		
	This file is part of Enhance.

	Copyright 

	License 

	Enhance is free software : you can redistribute it and /or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Enhance is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Enhance.If not, see < https://www.gnu.org/licenses/ >.



### pre-processor definitions

* description                          			: \brief description

### namespaces

* description                          			: \brief description 

### functions

* description                          			: \brief  description
* template parameters     	`<h3></h3>` 		: `<code>class ...</code>` : description
* Overloads		     	`<h3></h3>`
* Return		     	`<h3></h3>`     	: description
* Exceptions		     	`<h3></h3>`
* Complexity (Alg)	     	`<h3></h3>`
* average run time	   	`<h3></h3>`
* run time vs input table  	`<h3></h3>` 
* parameters		    				: `<i>[inout]</i>` : desc .  

### Variables

* description                          			: \brief  description
* Possible Values                      

### Classes

* description                          			: \brief  description
* hasErrorHandlers                     			: true / false
* prefered prefix/suffix 
* template parameters      	`<h3></h3> `
* Examples <h3></h3>				  

### Structures / Unions

* description                          			: \brief  description
* template parameters      	`<h3></h3>`
* prefered prefix/suffix           

### Enumeration

* description                          			: \brief  description
* Element                              			: `<i>[value]</i>` : desc.. 

### Typedefs

* description                          			: \brief  description


`<h3></h3>` displayed means that, the field must be under a header like so `<h3>[field]</h3>` 

## Example :

A sample documentation:	

sample_doc.enh.h (does not exist)
<code>
	
	/** 
	\file sample_doc.enh.h

	\brief File for demonstrating documentation.

	Created 10 May 2020

	This file is part of Enhance.

	Copyright 2020 Harith Manoj <harithpub@gmail.com>

	Enhance is free software : you can redistribute it and /or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Enhance is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Enhance. If not, see < https://www.gnu.org/licenses/>.


	*/
	
	/**
		\brief Function to add two numbers
		
		<h3>template</h3>
		<code>class arithmetic</code> : The type of numbers to be added, must be arithmetic type.
		
		<h3>Return</h3>
		The sum of the two arguments.
		
	*/
	template< class arithmetic>
	arithmetic add(arithmetic lhs, arithmetic rhs)
	{
		return lhs + rhs;
	}
</code>
