#python3 please
import os
import sys

map_count = 20
for i in range (2, map_count+1): 
    print ("""
            <tr>
                <td><!-- leave blank for autocounter --></td>
                <td><img src="../Map_Arene%d.png" /></td>
                <td>Map_Arene%d</td>
            </tr>""" % (i, i))