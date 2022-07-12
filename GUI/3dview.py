import sys

import numpy as np
from PyQt5.QtWidgets import QApplication
from pyqtgraph.opengl import GLViewWidget, MeshData, GLMeshItem
from PyQt5 import QtCore, QtGui, QtWidgets
from pyqtgraph import Vector
from pyqtgraph import mkColor
from stl import mesh
import PyQt5


if __name__ == "__main__":
    app = QApplication(sys.argv)
    view = GLViewWidget()
    # https://ozeki.hu/attachments/116/Eiffel_tower_sample.STL
    stl_mesh = mesh.Mesh.from_file('propuesta.stl')

    points = stl_mesh.points.reshape(-1, 3)
    faces = np.arange(points.shape[0]).reshape(-1, 3)

    mesh_data = MeshData(vertexes=points, faces=faces)
    mesh = GLMeshItem(meshdata=mesh_data, smooth=True, drawFaces=True, drawEdges=True, edgeColor=(0, 0, 0, 1))
    mesh.setColor(mkColor(192, 192, 192))
    view.setBackgroundColor(255, 255, 255, 255)
    view.addItem(mesh)
    position = Vector(0, 0, 0)
    print(view.cameraPosition())
    view.show()
    app.exec()