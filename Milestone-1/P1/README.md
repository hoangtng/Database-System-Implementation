readme 
=========
Test driver for Assignment 1 heap DBFile (ICS 421 Fall 2024) 

This test driver gives a menu-based interface to three options that allows you to test your code:
	1. load (read a tpch file and write it out a heap DBFile)
	2. scan (read records from an existing heap DBFile)
	3. scan & filter (read records and filter using a CNF predicate)

Note that the driver only works with the tpch files (generated using the dbgen program). 

To compile the driver, first install `bison` and `flex` package in linux:
```
apt-get install bison
apt-get install flex
```

Then type
```
make 
```

*Note*: If the `make` command returns "/usr/bin/ld: cannot find -lfl", you will have to install `libfl-dev` in your system. Ubuntu system can install it by typing 
```
apt-get install libfl-dev
```

To run the driver, type
```
./test.out
```
and follow the on-screen instructions.

Using the driver:
==================

1. SETTINGS: The following variables control the various file locations and they are declared in test.cc (just after the #include header declarations):
	
	* dbfile_dir -- this is where the created heap db-files will be stored. By default, this is set to "../data/bin/" (thus all the heap dbfiles will be created in the "data" directory).

	* tpch_dir -- this stores the directory path where the tpch-files can be found. The "../data/10M/" directory already has the required table files generated beforehand. There will be two tpch-files: 10M and 1G. Currently we only provide the 10M data, while the 1G data may be used for evaluate your program in the future. If you want to test on the 1G data, run these commands:
	
	```shell
	git clone https://github.com/electrum/tpch-dbgen.git 
	cd tpch-dbgen/
	make
	./dbgen -s 1

	```
	This will generate 8 *.tbl files containing the data in CSV format with `|` separator
	

	By default, tpch_dir is set to "../data/10M/".  

	* catalog_path -- this stores the catalog file path. By default this is set to "". Again, if you are running the driver from CISE linux machines you donot have to change this setting.

2. Compile and execute the driver. Select the load option to convert the tpch-files into heap dbfiles. The heap file is written in the dbfile_dir and have the extension ".bin".

3. Once load of a file has been selected, you can select option 2 or 3 to scan/filter all the records from the heap DBfile.  If option 3 is selected, a CNF should be supplied. Some example CNF's are given below. They are numbered q1,q2..q12. Use the table below to identify the tpch file associated with each CNF.
     	table    |   CNF
 ---------------------------------------
        region    |  q1 q2   
        nation    |  q3   
        supplier  |  q4 q5
        customer  |  q6
        part      |  q7   
        partsupp  |  q8 q9
        orders    |  q10                
        lineitem  |  q11 q12 

The expected output for these CNF's can be found in the file "output.log"

*Note*: each clause in a CNF must be surrounded by `()`, even if there is only one clause. 

Example CNF's
================

q1 
(r_name = 'EUROPE')

q2 
(r_name < 'MIDDLE EAST') AND
(r_regionkey > 1)

q3 
(n_regionkey = 3) AND
(n_nationkey > 10) AND
(n_name > 'JAPAN')

q4 
(s_suppkey < 10)

q5
(s_nationkey = 18) AND
(s_acctbal > 1000) AND
(s_suppkey < 400)

q6
(c_nationkey = 23) AND
(c_mktsegment = 'FURNITURE') AND
(c_acctbal > 7023.99) AND
(c_acctbal < 7110.83)


q7 
(p_brand = 'Brand#13') AND
(p_retailprice > 500.0) AND
(p_retailprice < 930.0) AND
(p_size > 28) AND
(p_size < 1000000)

q8 
(ps_supplycost > 999.98)

q9 
(ps_availqty < 10) AND
(ps_supplycost > 100.0) AND
(ps_suppkey < 300) 

q10 
(o_orderpriority = '1-URGENT') AND
(o_orderstatus = 'O') AND
(o_shippriority = 0) AND
(o_totalprice > 1015.68) AND
(o_totalprice < 1051.89)

q11
(l_shipdate > '1994-01-01') AND
(l_shipdate < '1994-01-07') AND
(l_discount > 0.05) AND
(l_discount < 0.06) AND
(l_quantity = 4.0) 


q12
(l_orderkey > 100) AND
(l_orderkey < 1000) AND
(l_partkey > 100) AND
(l_partkey < 5000) AND
(l_shipmode = 'AIR') AND
(l_linestatus = 'F') AND
(l_tax < 0.07)
