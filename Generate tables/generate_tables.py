# Author: Pedro Pinheiro

import generate_java_table
import generate_csharp_table

# TODO : Move to csv and latex directories. Generate operator tables
print("Generating Java table")
generate_java_table.generate()
print("Generating C# table")
generate_csharp_table.generate()
print("Done")

