
1. genomeGenerate
Read A,C,G,T and any other characters as N.

Two phases
----------
1. Use suffix array technique to find MMP or Maximal Mappable Prefix.
2. Stitch parts of a read sequence to build the alignment of the read.
We call parts of a read seeds. What are anchor seeds? 
How would we choose anchors? What are the genomic windows?
How do we use local sequence alignments when stitching seeds?

References
----------
dobin13, dobin13supp