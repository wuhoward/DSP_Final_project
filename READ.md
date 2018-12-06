
# Acoustic Feature based Mixture Model

### Concept Matching
While trying to get specific information from the search engine, we won't be satisfied if the engine simply returns those documents containing the provided keywords. On the contrary, a good search engine must be able to understand the concept behind our query and show us all related documents, even without the keywords! To achieve this, we must expand our query, i.e., find other keywords closely related to the user's intention. 

Our method is based on [Regularized Estimation of Mixture Models for Robust Pseudo-Relevance Feedback](http://sifaka.cs.uiuc.edu/czhai/pub/sigir06-reg.pdf). We used [trec_eval](https://github.com/usnistgov/trec_eval) to evaluate our result. On 5047 documents of Yahoo News Dataset with 163 queries, we improved the mean average precision (MAP) of retrieved documents over the baseline by 20%

**Query expansion:** Given the query Q from N documents with highest scores (top-N documents), we want to find other terms semantically related to Q.

### Original Language Model
The naive model return the top-N documents ranked by the following score function, where V is the lexicon:

$$S(d,Q)=\prod_{w \in V}P(w|θ_d)^{P(w|Q)}$$

### Word-based Mixture Model
Top-N documents, denoted as D, are used for estimating a query-related term distribution $\theta_R$ (unigram language model). For each word w in document d (d belongs to D), it is generated from either query-related model $\theta_R$ with probability $\alpha_d$  or background model $θ_B$ with probability $1-\alpha_d$. $\alpha_d$ is document-dependent. 

**Likelihood Function:**
Find $\theta_R$ and a set of $\alpha_d$ for each document d in D maximizing $F(\theta_R, \alpha_d)$.

$$F(\theta_R,\alpha_d)=L(\theta_R,\alpha_d)G(\theta_R) \\
L(\theta_R,\alpha_d|D)=\prod_{d \in D}\prod_{w \in V}[\alpha_dP(w|\theta_R)+(1-\alpha_d)P(w|\theta_B)]^{c(w,d)} \\
G(\theta_R)=\prod_{w \in V}P(w|\theta_R)^{\mu P(w|Q)}$$

**EM:**
Estimate $\alpha_d$ for each document d in D and $\theta_R$ by EM:

**E step:**
 
$$P(\theta_R|w,d)=\frac{\alpha_dP(w|\theta_R)}{α_d P(w|\theta_R)+(1-\alpha_d)P(w|\theta_B)}$$

$P(\theta_R|w,d)$ is posterior probability of w generating from $\theta_R$.

**M step:**

$$α_d=\frac{\sum_{w \in V}P(θ_R |w,d)c(w,d))}{\sum_{w \in V}c(w,d)}$$

$$P(w|\theta_R)=\frac{\sum_{d \in D}P(\theta_R|w,d)c(w,d)+\mu P(w|Q))}{\sum_{w \in V}\sum_{d \in D}P(\theta_R|w,d)c(w,d)+\mu}$$

**Testing Phase:**
$P(w|\theta_R)$ is used to replace $P(w|Q)$ in the original document ranking equation.

