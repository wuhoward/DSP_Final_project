
# Acoustic Feature based Mixture Model

### Concept Matching
While trying to get specific information from the search engine, we won't be satisfied if the engine simply returns those documents containing the provided keywords. On the contrary, a good search engine must be able to understand the concept behind our query and show us all related documents, even without the keywords! To achieve this, we must expand our query, i.e., find other keywords closely related to the user's intention. 

Our method is based on [Regularized Estimation of Mixture Models for Robust Pseudo-Relevance Feedback](http://sifaka.cs.uiuc.edu/czhai/pub/sigir06-reg.pdf). We used [trec_eval](https://github.com/usnistgov/trec_eval) to evaluate our result. On 5047 documents of Yahoo News Dataset with 163 queries, we improved the mean average precision (MAP) of retrieved documents over the baseline by 20%

**Query expansion:** Given the query Q from N documents with highest scores (top-N documents), we want to find other terms semantically related to Q.

### Original Language Model
The naive model return the top-N documents ranked by the following score function, where V is the lexicon:

<p align="center"><img alt="$$S(d,Q)=\prod_{w \in V}P(w|θ_d)^{P(w|Q)}$$" src="svgs/0b7b3a4ed93e177eb88f5a3254269625.png?invert_in_darkmode" align="middle" width="200.6136pt" height="37.765695pt"/></p>

### Word-based Mixture Model
Top-N documents, denoted as D, are used for estimating a query-related term distribution <img alt="$\theta_R$" src="svgs/cd4914230768b7ddbf66302324036950.png?invert_in_darkmode" align="middle" width="17.61276pt" height="22.745910000000016pt"/> (unigram language model). For each word w in document d (d belongs to D), it is generated from either query-related model <img alt="$\theta_R$" src="svgs/cd4914230768b7ddbf66302324036950.png?invert_in_darkmode" align="middle" width="17.61276pt" height="22.745910000000016pt"/> with probability <img alt="$α_d$" src="svgs/b94aed9ed555ad6498dedda3be0f2c8c.png?invert_in_darkmode" align="middle" width="6.817552500000002pt" height="14.102549999999994pt"/>  or background model <img alt="$θ_B$" src="svgs/d6880f6bb3acd411bceafe33eef6dd37.png?invert_in_darkmode" align="middle" width="10.453410000000002pt" height="14.102549999999994pt"/> with probability <img alt="$1-α_d$" src="svgs/eef289a0be45b50f9a77d689df3fe475.png?invert_in_darkmode" align="middle" width="35.049465pt" height="21.10812pt"/>. <img alt="$α_d$" src="svgs/b94aed9ed555ad6498dedda3be0f2c8c.png?invert_in_darkmode" align="middle" width="6.817552500000002pt" height="14.102549999999994pt"/> is document-dependent. 

**Likelihood Function:**
Find <img alt="$\theta_R$" src="svgs/cd4914230768b7ddbf66302324036950.png?invert_in_darkmode" align="middle" width="17.61276pt" height="22.745910000000016pt"/> and a set of <img alt="$α_d$" src="svgs/b94aed9ed555ad6498dedda3be0f2c8c.png?invert_in_darkmode" align="middle" width="6.817552500000002pt" height="14.102549999999994pt"/> for each document d in D maximizing <img alt="$F(\theta_R, α_d)$" src="svgs/f9ab939bf2fc96efbe2970a94b2cd69c.png?invert_in_darkmode" align="middle" width="58.977765000000005pt" height="24.56552999999997pt"/>.

<p align="center"><img alt="$$F(\theta_R,α_d)=L(\theta_R,α_d)G(\theta_R) \\&#10;L(\theta_R,α_d|D)=\prod_{d \in D}\prod_{w \in V}[α_dP(w|\theta_R)+(1-α_d)P(w|\theta_B)]^{c(w,d)} \\&#10;G(\theta_R)=\prod_{w \in V}P(w|\theta_R)^{\mu P(w|Q)}$$" src="svgs/981e12bcb58a69feefc0aa5287772cb3.png?invert_in_darkmode" align="middle" width="780.1265999999999pt" height="37.893570000000004pt"/></p>

**EM:**
Estimate <img alt="$α_d$" src="svgs/b94aed9ed555ad6498dedda3be0f2c8c.png?invert_in_darkmode" align="middle" width="6.817552500000002pt" height="14.102549999999994pt"/> for each document d in D and <img alt="$\theta_R$" src="svgs/cd4914230768b7ddbf66302324036950.png?invert_in_darkmode" align="middle" width="17.61276pt" height="22.745910000000016pt"/> by EM:

**E step:**
 
<p align="center"><img alt="$$P(\theta_R|w,d)=\frac{α_dP(w|\theta_R)}{α_d P(w|\theta_R)+(1-α_d)P(w|\theta_B)}$$" src="svgs/3489ede845ee91e141f8ff74de852461.png?invert_in_darkmode" align="middle" width="299.22585pt" height="38.773514999999996pt"/></p>

<img alt="$P(\theta_R|w,d)$" src="svgs/4de34deb115bb122d2e26b5e7211c0ff.png?invert_in_darkmode" align="middle" width="76.53574499999999pt" height="24.56552999999997pt"/> is posterior probability of w generating from <img alt="$\theta_R$" src="svgs/cd4914230768b7ddbf66302324036950.png?invert_in_darkmode" align="middle" width="17.61276pt" height="22.745910000000016pt"/>.

**M step:**

<p align="center"><img alt="$$α_d=\frac{\sum_{w \in V}P(θ_R |w,d)c(w,d))}{\sum_{w \in V}c(w,d)}$$" src="svgs/15a31427426d853c18437375f3cbea2e.png?invert_in_darkmode" align="middle" width="205.1016pt" height="41.617125pt"/></p>

<p align="center"><img alt="$$P(w|\theta_R)=\frac{\sum_{d \in D}P(\theta_R|w,d)c(w,d)+\mu P(w|Q))}{\sum_{w \in V}\sum_{d \in D}P(\theta_R|w,d)c(w,d)+\mu}$$" src="svgs/f71d6c021764d725a6a0ad75920cc94c.png?invert_in_darkmode" align="middle" width="348.79845pt" height="41.617125pt"/></p>

**Testing Phase:**
<img alt="$P(w|\theta_R)$" src="svgs/ebe176c6e23f8581fbfbf67da4a0a189.png?invert_in_darkmode" align="middle" width="60.722805pt" height="24.56552999999997pt"/> is used to replace <img alt="$P(w|Q)$" src="svgs/362805784cf392925daf5cbe0f050d65.png?invert_in_darkmode" align="middle" width="55.197945pt" height="24.56552999999997pt"/> in the original document ranking equation.

