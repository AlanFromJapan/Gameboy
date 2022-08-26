#python3 please
import os
import sys


with open("maps.html", "w") as f:
    f.write("<html><body><table>")
    for fname in os.listdir("."):
        if fname[-4:].lower() == ".png":
            f.write("""
                    <tr>
                        <td><!-- leave blank for autocounter --></td>
                        <td><img src="%s" /></td>
                        <td>%s</td>
                    </tr>""" % (fname, fname[:-4]))
    f.write("</table></body></html>")