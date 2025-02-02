import matplotlib.pyplot as plt

# Logs containing accuracy for each epoch
logs = """
The accuracy train is : 80.542328
The accuracy test is : 88.738095
The label 7.000000
Epoch 0: Prediction = 7
The accuracy train is : 92.441799
The accuracy test is : 91.666667
The label 3.000000
Epoch 5: Prediction = 3
The accuracy train is : 93.500000
The accuracy test is : 92.571429
The label 4.000000
Epoch 10: Prediction = 4
The accuracy train is : 93.888889
The accuracy test is : 91.809524
The label 5.000000
Epoch 15: Prediction = 5
The accuracy train is : 94.126984
The accuracy test is : 92.690476
The label 6.000000
Epoch 20: Prediction = 6
The accuracy train is : 94.309524
The accuracy test is : 93.023810
The label 9.000000
Epoch 25: Prediction = 9
The accuracy train is : 94.544974
The accuracy test is : 92.023810
The label 4.000000
Epoch 30: Prediction = 4
The accuracy train is : 94.722222
The accuracy test is : 92.904762
The label 0.000000
Epoch 35: Prediction = 0
The accuracy train is : 94.798942
The accuracy test is : 92.761905
The label 8.000000
Epoch 40: Prediction = 8
The accuracy train is : 94.928571
The accuracy test is : 92.833333
The label 3.000000
Epoch 45: Prediction = 3
The accuracy train is : 95.066138
The accuracy test is : 93.047619
The label 8.000000
Epoch 50: Prediction = 8
The accuracy train is : 95.164021
The accuracy test is : 93.404762
The label 2.000000
Epoch 55: Prediction = 2
The accuracy train is : 95.013228
The accuracy test is : 92.000000
The label 7.000000
Epoch 60: Prediction = 7
The accuracy train is : 95.383598
The accuracy test is : 92.619048
The label 8.000000
Epoch 65: Prediction = 8
The accuracy train is : 95.328042
The accuracy test is : 92.928571
The label 0.000000
Epoch 70: Prediction = 0
The accuracy train is : 95.470899
The accuracy test is : 92.904762
The label 2.000000
Epoch 75: Prediction = 2
The accuracy train is : 95.558201
The accuracy test is : 92.952381
The label 7.000000
Epoch 80: Prediction = 7
The accuracy train is : 95.420635
The accuracy test is : 93.095238
The label 4.000000
Epoch 85: Prediction = 4
The accuracy train is : 95.500000
The accuracy test is : 92.476190
The label 7.000000
Epoch 90: Prediction = 7
The accuracy train is : 95.574074
The accuracy test is : 92.904762
The label 8.000000
Epoch 95: Prediction = 8
The accuracy train is : 95.642857
The accuracy test is : 92.761905
The label 7.000000
Epoch 100: Prediction = 7
The accuracy train is : 95.626984
The accuracy test is : 92.642857
The label 1.000000
Epoch 105: Prediction = 1
The accuracy train is : 95.666667
The accuracy test is : 93.190476
The label 2.000000
Epoch 110: Prediction = 2
The accuracy train is : 95.769841
The accuracy test is : 93.238095
The label 3.000000
Epoch 115: Prediction = 3
The accuracy train is : 95.809524
The accuracy test is : 92.119048
The label 7.000000
Epoch 120: Prediction = 7
The accuracy train is : 95.716931
The accuracy test is : 92.619048
The label 2.000000
Epoch 125: Prediction = 2
The accuracy train is : 95.722222
The accuracy test is : 92.500000
The label 8.000000
Epoch 130: Prediction = 5
The accuracy train is : 95.846561
The accuracy test is : 92.690476
The label 4.000000
Epoch 135: Prediction = 4
The accuracy train is : 95.978836
The accuracy test is : 92.738095
The label 4.000000
Epoch 140: Prediction = 4
The accuracy train is : 95.968254
The accuracy test is : 92.928571
The label 1.000000
Epoch 145: Prediction = 1
The accuracy train is : 95.941799
The accuracy test is : 93.000000
The label 5.000000
Epoch 150: Prediction = 5
The accuracy train is : 95.931217
The accuracy test is : 92.809524
The label 2.000000
Epoch 155: Prediction = 2
The accuracy train is : 96.063492
The accuracy test is : 92.476190
The label 8.000000
Epoch 160: Prediction = 8
The accuracy train is : 95.923280
The accuracy test is : 92.738095
The label 6.000000
Epoch 165: Prediction = 6
The accuracy train is : 96.055556
The accuracy test is : 92.452381
The label 6.000000
Epoch 170: Prediction = 6
The accuracy train is : 96.066138
The accuracy test is : 92.357143
The label 7.000000
Epoch 175: Prediction = 7
The accuracy train is : 96.037037
The accuracy test is : 92.928571
The label 0.000000
Epoch 180: Prediction = 0
The accuracy train is : 96.113757
The accuracy test is : 92.785714
The label 4.000000
Epoch 185: Prediction = 4
The accuracy train is : 96.076720
The accuracy test is : 92.595238
The label 9.000000
Epoch 190: Prediction = 9
The accuracy train is : 96.074074
The accuracy test is : 92.500000
The label 3.000000
Epoch 195: Prediction = 3
The accuracy train is : 96.047619
The accuracy test is : 92.714286
The label 5.000000
Epoch 200: Prediction = 5
The accuracy train is : 96.068783
The accuracy test is : 92.571429
The label 0.000000
Epoch 205: Prediction = 0
The accuracy train is : 96.044974
The accuracy test is : 92.428571
The label 3.000000
Epoch 210: Prediction = 3
The accuracy train is : 96.211640
The accuracy test is : 92.476190
The label 8.000000
Epoch 215: Prediction = 8
The accuracy train is : 96.145503
The accuracy test is : 92.595238
The label 9.000000
Epoch 220: Prediction = 9
The accuracy train is : 96.201058
The accuracy test is : 92.833333
The label 5.000000
Epoch 225: Prediction = 5
The accuracy train is : 96.169312
The accuracy test is : 92.571429
The label 5.000000
Epoch 230: Prediction = 5
The accuracy train is : 96.137566
The accuracy test is : 92.547619
The label 6.000000
Epoch 235: Prediction = 6
The accuracy train is : 96.219577
The accuracy test is : 92.357143
The label 2.000000
Epoch 240: Prediction = 2
The accuracy train is : 96.201058
The accuracy test is : 92.761905
The label 3.000000
Epoch 245: Prediction = 3
The accuracy train is : 96.227513
The accuracy test is : 92.023810
The label 1.000000
Epoch 250: Prediction = 1
The accuracy train is : 96.156085
The accuracy test is : 92.619048
The label 7.000000
Epoch 255: Prediction = 7
The accuracy train is : 96.259259
The accuracy test is : 92.333333
The label 0.000000
Epoch 260: Prediction = 0
The accuracy train is : 96.132275
The accuracy test is : 92.071429
The label 8.000000
Epoch 265: Prediction = 8
The accuracy train is : 96.219577
The accuracy test is : 92.071429
The label 9.000000
Epoch 270: Prediction = 9
The accuracy train is : 96.227513
The accuracy test is : 92.166667
The label 4.000000
Epoch 275: Prediction = 4
The accuracy train is : 96.145503
The accuracy test is : 92.761905
The label 7.000000
Epoch 280: Prediction = 7
The accuracy train is : 96.164021
The accuracy test is : 93.095238
The label 1.000000
Epoch 285: Prediction = 1
The accuracy train is : 96.259259
The accuracy test is : 91.904762
The label 4.000000
Epoch 290: Prediction = 4
The accuracy train is : 96.378307
The accuracy test is : 92.333333
The label 0.000000
Epoch 295: Prediction = 0
The accuracy train is : 96.232804
The accuracy test is : 92.380952
The label 6.000000
Epoch 300: Prediction = 6
The accuracy train is : 96.391534
The accuracy test is : 92.309524
The label 3.000000
Epoch 305: Prediction = 3
The accuracy train is : 96.338624
The accuracy test is : 92.523810
The label 5.000000
Epoch 310: Prediction = 5
The accuracy train is : 96.293651
The accuracy test is : 92.309524
The label 3.000000
Epoch 315: Prediction = 3
The accuracy train is : 96.444444
The accuracy test is : 92.071429
The label 1.000000
Epoch 320: Prediction = 1
The accuracy train is : 96.484127
The accuracy test is : 92.500000
The label 5.000000
Epoch 325: Prediction = 5
The accuracy train is : 96.386243
The accuracy test is : 91.928571
The label 9.000000
Epoch 330: Prediction = 9
The accuracy train is : 96.404762
The accuracy test is : 92.166667
The label 2.000000
Epoch 335: Prediction = 2
The accuracy train is : 96.470899
The accuracy test is : 92.285714
The label 3.000000
Epoch 340: Prediction = 3
The accuracy train is : 96.391534
The accuracy test is : 91.595238
The label 2.000000
Epoch 345: Prediction = 2
The accuracy train is : 96.388889
The accuracy test is : 92.190476
The label 2.000000
Epoch 350: Prediction = 2
The accuracy train is : 96.457672
The accuracy test is : 92.571429
The label 4.000000
Epoch 355: Prediction = 4
The accuracy train is : 96.523810
The accuracy test is : 92.452381
The label 2.000000
Epoch 360: Prediction = 2
The accuracy train is : 96.394180
The accuracy test is : 91.928571
The label 4.000000
Epoch 365: Prediction = 4
The accuracy train is : 96.476190
The accuracy test is : 92.452381
The label 0.000000
Epoch 370: Prediction = 0
The accuracy train is : 96.447090
The accuracy test is : 92.404762
The label 2.000000
Epoch 375: Prediction = 8
The accuracy train is : 96.648148
The accuracy test is : 91.595238
The label 5.000000
Epoch 380: Prediction = 5
The accuracy train is : 96.492063
The accuracy test is : 91.904762
The label 9.000000
Epoch 385: Prediction = 9
The accuracy train is : 96.473545
The accuracy test is : 92.023810
The label 5.000000
Epoch 390: Prediction = 5
The accuracy train is : 96.460317
The accuracy test is : 92.523810
The label 1.000000
Epoch 395: Prediction = 1
The accuracy train is : 96.523810
The accuracy test is : 91.928571
The label 1.000000
Epoch 400: Prediction = 1
The accuracy train is : 96.457672
The accuracy test is : 92.071429
The label 5.000000
Epoch 405: Prediction = 5
The accuracy train is : 96.500000
The accuracy test is : 92.190476
The label 5.000000
Epoch 410: Prediction = 5
The accuracy train is : 96.407407
The accuracy test is : 92.285714
The label 1.000000
Epoch 415: Prediction = 1
The accuracy train is : 96.470899
The accuracy test is : 91.833333
The label 5.000000
Epoch 420: Prediction = 6
The accuracy train is : 96.552910
The accuracy test is : 92.547619
The label 9.000000
Epoch 425: Prediction = 9
The accuracy train is : 96.544974
The accuracy test is : 92.428571
The label 1.000000
Epoch 430: Prediction = 1
The accuracy train is : 96.388889
The accuracy test is : 92.500000
The label 5.000000
Epoch 435: Prediction = 5
The accuracy train is : 96.460317
The accuracy test is : 92.023810
The label 8.000000
Epoch 440: Prediction = 8
The accuracy train is : 96.428571
The accuracy test is : 92.500000
The label 1.000000
Epoch 445: Prediction = 1
The accuracy train is : 96.470899
The accuracy test is : 91.738095
The label 8.000000
Epoch 450: Prediction = 8
The accuracy train is : 96.505291
The accuracy test is : 92.142857
The label 2.000000
Epoch 455: Prediction = 2
The accuracy train is : 96.412698
The accuracy test is : 92.119048
The label 6.000000
Epoch 460: Prediction = 6
The accuracy train is : 96.531746
The accuracy test is : 91.619048
The label 7.000000
Epoch 465: Prediction = 7
The accuracy train is : 96.531746
The accuracy test is : 92.238095
The label 8.000000
Epoch 470: Prediction = 8
The accuracy train is : 96.645503
The accuracy test is : 92.119048
The label 6.000000
Epoch 475: Prediction = 6
The accuracy train is : 96.542328
The accuracy test is : 92.309524
The label 4.000000
Epoch 480: Prediction = 4
The accuracy train is : 96.542328
The accuracy test is : 92.261905
The label 0.000000
Epoch 485: Prediction = 0
The accuracy train is : 96.547619
The accuracy test is : 91.523810
The label 5.000000
Epoch 490: Prediction = 5
The accuracy train is : 96.492063
The accuracy test is : 92.285714
The label 6.000000
Epoch 495: Prediction = 6
The accuracy train is : 96.592593
The accuracy test is : 92.095238
The label 0.000000
Epoch 500: Prediction = 0
The accuracy train is : 96.669312
The accuracy test is : 92.238095
The label 2.000000
Epoch 505: Prediction = 2
The accuracy train is : 96.550265
The accuracy test is : 91.880952
The label 4.000000
Epoch 510: Prediction = 4
The accuracy train is : 96.552910
The accuracy test is : 92.904762
The label 6.000000
Epoch 515: Prediction = 6
The accuracy train is : 96.666667
The accuracy test is : 92.119048
The label 7.000000
Epoch 520: Prediction = 7
The accuracy train is : 96.563492
The accuracy test is : 91.809524
The label 2.000000
Epoch 525: Prediction = 2
The accuracy train is : 96.616402
The accuracy test is : 91.476190
The label 0.000000
Epoch 530: Prediction = 0
The accuracy train is : 96.605820
The accuracy test is : 91.761905
The label 6.000000
Epoch 535: Prediction = 6
The accuracy train is : 96.629630
The accuracy test is : 92.119048
The label 0.000000
Epoch 540: Prediction = 0
The accuracy train is : 96.531746
The accuracy test is : 91.500000
The label 0.000000
Epoch 545: Prediction = 0
The accuracy train is : 96.576720
The accuracy test is : 92.142857
The label 6.000000
Epoch 550: Prediction = 6
The accuracy train is : 96.708995
The accuracy test is : 92.000000
The label 8.000000
Epoch 555: Prediction = 8
The accuracy train is : 96.552910
The accuracy test is : 92.261905
The label 0.000000
Epoch 560: Prediction = 0
The accuracy train is : 96.571429
The accuracy test is : 92.238095
The label 0.000000
Epoch 565: Prediction = 0
The accuracy train is : 96.600529
The accuracy test is : 92.142857
The label 6.000000
Epoch 570: Prediction = 6
The accuracy train is : 96.576720
The accuracy test is : 91.952381
The label 0.000000
Epoch 575: Prediction = 0
The accuracy train is : 96.648148
The accuracy test is : 92.190476
The label 3.000000
Epoch 580: Prediction = 3
The accuracy train is : 96.637566
The accuracy test is : 92.071429
The label 7.000000
Epoch 585: Prediction = 7
The accuracy train is : 96.664021
The accuracy test is : 92.047619
The label 4.000000
Epoch 590: Prediction = 4
The accuracy train is : 96.603175
The accuracy test is : 92.047619
The label 4.000000
Epoch 595: Prediction = 9
The accuracy train is : 96.703704
The accuracy test is : 92.047619
The label 8.000000
Epoch 600: Prediction = 8
The accuracy train is : 96.738095
The accuracy test is : 92.095238
The label 6.000000
Epoch 605: Prediction = 6
The accuracy train is : 96.661376
The accuracy test is : 91.666667
The label 4.000000
Epoch 610: Prediction = 4
The accuracy train is : 96.616402
The accuracy test is : 91.904762
The label 2.000000
Epoch 615: Prediction = 2
The accuracy train is : 96.669312
The accuracy test is : 92.261905
The label 4.000000
Epoch 620: Prediction = 4
The accuracy train is : 96.708995
The accuracy test is : 91.833333
The label 5.000000
Epoch 625: Prediction = 5
The accuracy train is : 96.637566
The accuracy test is : 91.904762
The label 4.000000
Epoch 630: Prediction = 4
The accuracy train is : 96.693122
The accuracy test is : 92.380952
The label 0.000000
Epoch 635: Prediction = 0
The accuracy train is : 96.743386
The accuracy test is : 91.880952
The label 0.000000
Epoch 640: Prediction = 0
The accuracy train is : 96.746032
The accuracy test is : 91.809524
The label 1.000000
Epoch 645: Prediction = 1
The accuracy train is : 96.685185
The accuracy test is : 91.714286
The label 4.000000
Epoch 650: Prediction = 4
The accuracy train is : 96.814815
The accuracy test is : 91.738095
The label 7.000000
Epoch 655: Prediction = 7
The accuracy train is : 96.716931
The accuracy test is : 91.761905
The label 6.000000
Epoch 660: Prediction = 6
The accuracy train is : 96.761905
The accuracy test is : 92.000000
The label 1.000000
Epoch 665: Prediction = 1
The accuracy train is : 96.738095
The accuracy test is : 92.166667
The label 0.000000
Epoch 670: Prediction = 0
The accuracy train is : 96.833333
The accuracy test is : 91.976190
The label 9.000000
Epoch 675: Prediction = 9
The accuracy train is : 96.756614
The accuracy test is : 92.166667
The label 6.000000
Epoch 680: Prediction = 0
The accuracy train is : 96.764550
The accuracy test is : 91.690476
The label 8.000000
Epoch 685: Prediction = 8
The accuracy train is : 96.767196
The accuracy test is : 92.190476
The label 7.000000
Epoch 690: Prediction = 7
The accuracy train is : 96.653439
The accuracy test is : 91.904762
The label 7.000000
Epoch 695: Prediction = 7
The accuracy train is : 96.809524
The accuracy test is : 92.166667
The label 8.000000
Epoch 700: Prediction = 8
The accuracy train is : 96.759259
The accuracy test is : 91.904762
The label 7.000000
Epoch 705: Prediction = 7
The accuracy train is : 96.706349
The accuracy test is : 91.547619
The label 9.000000
Epoch 710: Prediction = 9
The accuracy train is : 96.727513
The accuracy test is : 92.309524
The label 0.000000
Epoch 715: Prediction = 0
The accuracy train is : 96.743386
The accuracy test is : 91.833333
The label 6.000000
Epoch 720: Prediction = 6
The accuracy train is : 96.722222
The accuracy test is : 91.404762
The label 2.000000
Epoch 725: Prediction = 2
The accuracy train is : 96.682540
The accuracy test is : 92.047619
The label 7.000000
Epoch 730: Prediction = 7
The accuracy train is : 96.828042
The accuracy test is : 91.880952
The label 9.000000
Epoch 735: Prediction = 9
The accuracy train is : 96.743386
The accuracy test is : 92.095238
The label 0.000000
Epoch 740: Prediction = 0
The accuracy train is : 96.740741
The accuracy test is : 91.690476
The label 9.000000
Epoch 745: Prediction = 9
The accuracy train is : 96.679894
The accuracy test is : 91.476190
The label 2.000000
Epoch 750: Prediction = 2
The accuracy train is : 96.711640
The accuracy test is : 91.571429
The label 2.000000
Epoch 755: Prediction = 3
The accuracy train is : 96.722222
The accuracy test is : 92.023810
The label 9.000000
Epoch 760: Prediction = 9
The accuracy train is : 96.791005
The accuracy test is : 92.023810
The label 6.000000
Epoch 765: Prediction = 6
The accuracy train is : 96.820106
The accuracy test is : 92.214286
The label 6.000000
Epoch 770: Prediction = 6
The accuracy train is : 96.804233
The accuracy test is : 91.500000
The label 6.000000
Epoch 775: Prediction = 6
The accuracy train is : 96.843915
The accuracy test is : 92.190476
The label 0.000000
Epoch 780: Prediction = 0
The accuracy train is : 96.925926
The accuracy test is : 91.619048
The label 5.000000
Epoch 785: Prediction = 5
The accuracy train is : 96.735450
The accuracy test is : 91.571429
The label 5.000000
Epoch 790: Prediction = 5
The accuracy train is : 96.724868
The accuracy test is : 91.714286
The label 2.000000
Epoch 795: Prediction = 2
The accuracy train is : 96.830688
The accuracy test is : 91.428571
The label 8.000000
Epoch 800: Prediction = 8
The accuracy train is : 96.788360
The accuracy test is : 91.904762
The label 9.000000
Epoch 805: Prediction = 9
The accuracy train is : 96.716931
The accuracy test is : 91.523810
The label 8.000000
Epoch 810: Prediction = 8
The accuracy train is : 96.748677
The accuracy test is : 91.904762
The label 7.000000
Epoch 815: Prediction = 7
The accuracy train is : 96.865079
The accuracy test is : 90.357143
The label 8.000000
Epoch 820: Prediction = 8
The accuracy train is : 96.698413
The accuracy test is : 91.738095
The label 3.000000
Epoch 825: Prediction = 1
The accuracy train is : 96.910053
The accuracy test is : 91.880952
The label 2.000000
Epoch 830: Prediction = 2
The accuracy train is : 96.801587
The accuracy test is : 91.833333
The label 2.000000
Epoch 835: Prediction = 2
The accuracy train is : 96.698413
The accuracy test is : 91.738095
The label 7.000000
Epoch 840: Prediction = 2
The accuracy train is : 97.002646
The accuracy test is : 91.357143
The label 7.000000
Epoch 845: Prediction = 7
The accuracy train is : 96.867725
The accuracy test is : 92.023810
The label 0.000000
Epoch 850: Prediction = 0
The accuracy train is : 96.862434
The accuracy test is : 91.380952
The label 2.000000
Epoch 855: Prediction = 2
The accuracy train is : 96.931217
The accuracy test is : 90.857143
The label 8.000000
Epoch 860: Prediction = 8
The accuracy train is : 96.796296
The accuracy test is : 91.547619
The label 7.000000
Epoch 865: Prediction = 7
The accuracy train is : 96.814815
The accuracy test is : 91.809524
The label 6.000000
Epoch 870: Prediction = 6
The accuracy train is : 96.859788
The accuracy test is : 91.738095
The label 8.000000
Epoch 875: Prediction = 8
The accuracy train is : 96.830688
The accuracy test is : 91.928571
The label 5.000000
Epoch 880: Prediction = 5
The accuracy train is : 96.880952
The accuracy test is : 91.904762
The label 9.000000
Epoch 885: Prediction = 9
The accuracy train is : 96.944444
The accuracy test is : 91.952381
The label 9.000000
Epoch 890: Prediction = 9
The accuracy train is : 96.785714
The accuracy test is : 91.404762
The label 0.000000
Epoch 895: Prediction = 0
The accuracy train is : 96.796296
The accuracy test is : 91.761905
The label 7.000000
Epoch 900: Prediction = 7
The accuracy train is : 96.891534
The accuracy test is : 91.785714
The label 4.000000
Epoch 905: Prediction = 4
The accuracy train is : 96.878307
The accuracy test is : 91.666667
The label 4.000000
Epoch 910: Prediction = 4
The accuracy train is : 96.849206
The accuracy test is : 91.738095
The label 2.000000
Epoch 915: Prediction = 2
The accuracy train is : 96.785714
The accuracy test is : 92.000000
The label 9.000000
Epoch 920: Prediction = 9
The accuracy train is : 96.822751
The accuracy test is : 91.595238
The label 0.000000
Epoch 925: Prediction = 0
The accuracy train is : 96.870370
The accuracy test is : 91.976190
The label 0.000000
Epoch 930: Prediction = 0
The accuracy train is : 96.907407
The accuracy test is : 91.238095
The label 4.000000
Epoch 935: Prediction = 4
The accuracy train is : 96.936508
The accuracy test is : 90.523810
The label 1.000000
Epoch 940: Prediction = 1
The accuracy train is : 96.857143
The accuracy test is : 91.500000
The label 7.000000
Epoch 945: Prediction = 7
The accuracy train is : 96.849206
The accuracy test is : 91.595238
The label 8.000000
Epoch 950: Prediction = 8
The accuracy train is : 96.891534
The accuracy test is : 91.571429
The label 3.000000
Epoch 955: Prediction = 3
The accuracy train is : 96.923280
The accuracy test is : 91.047619
The label 0.000000
Epoch 960: Prediction = 0
The accuracy train is : 96.907407
The accuracy test is : 91.452381
The label 1.000000
Epoch 965: Prediction = 1
The accuracy train is : 96.738095
The accuracy test is : 91.285714
The label 1.000000
Epoch 970: Prediction = 1
The accuracy train is : 96.923280
The accuracy test is : 91.428571
The label 8.000000
Epoch 975: Prediction = 8
The accuracy train is : 96.939153
The accuracy test is : 91.238095
The label 8.000000
Epoch 980: Prediction = 8
The accuracy train is : 96.851852
The accuracy test is : 91.666667
The label 7.000000
Epoch 985: Prediction = 1
The accuracy train is : 96.936508
The accuracy test is : 91.904762
The label 2.000000
Epoch 990: Prediction = 2
The accuracy train is : 97.007937
The accuracy test is : 91.619048
"""  
# Replace with your actual logs

train_accuracies = []
test_accuracies = []

# Extract training and testing accuracy
for line in logs.split('\n'):
    if 'The accuracy train is' in line:
        train_acc = float(line.split('The accuracy train is : ')[1].split()[0])
        
        train_accuracies.append(train_acc)
    if 'The accuracy test is' in line:
        test_acc = float(line.split('The accuracy test is : ')[1].split()[0])
        test_accuracies.append(test_acc)

print(train_accuracies);

epochs = range(len(train_accuracies))

plt.plot(epochs, train_accuracies, label='Train Accuracy')
plt.plot(epochs, test_accuracies, label='Test Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.title('Training and Testing Accuracy Over Epochs')
plt.show()
