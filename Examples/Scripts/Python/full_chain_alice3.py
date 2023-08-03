#!/usr/bin/env python3

from acts.examples.reconstruction import (
    addSeeding,
    TruthSeedRanges,
    SeedFinderConfigArg,
    SeedFinderOptionsArg,
    SeedFilterConfigArg,
    SpacePointGridConfigArg,
    SeedingAlgorithmConfigArg,
    SeedingAlgorithm,
    ParticleSmearingSigmas,
    addCKFTracks,
    TrackSelectorConfig,
    addAmbiguityResolution,
    AmbiguityResolutionConfig,
    addAmbiguityResolutionML,
    AmbiguityResolutionMLConfig,
)
from acts.examples.simulation import (
    addParticleGun,
    MomentumConfig,
    EtaConfig,
    ParticleConfig,
    addPythia8,
    addFatras,
    ParticleSelectorConfig,
    addDigitization,
)

from random import *
import os
import pathlib
import acts
import acts.examples
import alice3
from acts import UnitConstants as u


# def runALICE3fullchain(

heavyIonSim = True #True
pdg = 13 #13
npart = 10
bFieldZ = 2
nEvents = 5000
enableMat = True
simTypeString = "gun" if not heavyIonSim else "PbPb"

# ):

geo_dir = pathlib.Path.cwd().parent
outputDir = pathlib.Path(
    "/Users/achalume/alice/actsdir/acts/bin/output/python/ckf_" +
    simTypeString +
    "_" + str(pdg) + "_Bfield" + str(bFieldZ) + "_npart" +
    str(npart) + "_nEvents" + str(nEvents) +
    "_noseedconf_nobin_ambi_infl100_paramsckfv13_cfg10_pTmin500_z1300")

detector, trackingGeometry, decorators = alice3.buildALICE3Geometry(
    geo_dir, enableMat, False)
field = acts.ConstantBField(acts.Vector3(0.0, 0.0, bFieldZ * u.T))
rnd = acts.examples.RandomNumbers(seed=42)

s = acts.examples.Sequencer(events=nEvents, numThreads=-1)

"""
 ### Generate only pythia file
s = addPythia8(
    s,
    npileup=1,
    beam=acts.PdgParticle.eLead,
    cmsEnergy=5 * acts.UnitConstants.TeV,
    # hardProcess=["Top:qqbar2ttbar=on"],
    # npileup=200,
    vtxGen=acts.examples.GaussianVertexGenerator(
        stddev=acts.Vector4(0.0125 * u.mm, 0.0125 *
                            u.mm, 55.5 * u.mm, 5.0 * u.ns),
        mean=acts.Vector4(0, 0, 0, 0),
    ),
    rnd=rnd,
    outputDirRoot=outputDir,
)
 ###
"""

if not heavyIonSim:
    addParticleGun(
        s,
        MomentumConfig(0.5 * u.GeV, 10.0 * u.GeV, transverse=True),
        EtaConfig(-4, 4, uniform=True),
        ParticleConfig(npart, acts.PdgParticle.ePionPlus,
                       randomizeCharge=True),
        # multiplicity=mult,
        rnd=rnd,
    )
else:
    s = addPythia8(
        s,
        npileup=1,
        beam=acts.PdgParticle.eLead,
        cmsEnergy=5 * acts.UnitConstants.TeV,
        # hardProcess=["Top:qqbar2ttbar=on"],
        # npileup=200,
        vtxGen=acts.examples.GaussianVertexGenerator(
            stddev=acts.Vector4(0.0125 * u.mm, 0.0125 *
                                u.mm, 55.5 * u.mm, 5.0 * u.ns),
            mean=acts.Vector4(0, 0, 0, 0),
        ),
        rnd=rnd,
        outputDirRoot=outputDir,
    )
s = addFatras(
    s,
    trackingGeometry,
    field,
    rnd=rnd,
    preSelectParticles=ParticleSelectorConfig(
        eta=(-4.0, 4.0), pt=(500 * u.MeV, None), removeNeutral=False),
    pMin=500 * u.MeV,
    enableInteractions=True,
    outputDirRoot=outputDir,
)
s = addDigitization(
    s,
    trackingGeometry,
    field,
    digiConfigFile=geo_dir / "acts/bin/alice3-smearing-config.json",
    outputDirRoot=outputDir,
    rnd=rnd,
)
s = addSeeding(
    s,
    trackingGeometry,
    field,
    TruthSeedRanges(pt=(0.5 * u.GeV, None),
                    eta=(-4.0, 4.0), nHits=(7, None)),
    SeedFinderConfigArg(
        r=(None, 200 * u.mm),
        deltaR=(1. * u.mm, 60 * u.mm),
        collisionRegion=(-250 * u.mm, 250 * u.mm),
        z=(-1300 * u.mm, 1300 * u.mm),
        maxSeedsPerSpM=1,
        sigmaScattering=5.,
        radLengthPerSeed=0.1,
        minPt=500 * u.MeV, #was 100
        impactMax=3. * u.mm,
        cotThetaMax=27.2899,
        seedConfirmation=False,
        centralSeedConfirmationRange=acts.SeedConfirmationRangeConfig(
            zMinSeedConf=-620 * u.mm,
            zMaxSeedConf=620 * u.mm,
            rMaxSeedConf=36 * u.mm,
            nTopForLargeR=1,
            nTopForSmallR=2,
        ),
        forwardSeedConfirmationRange=acts.SeedConfirmationRangeConfig(
            zMinSeedConf=-1220 * u.mm,
            zMaxSeedConf=1220 * u.mm,
            rMaxSeedConf=36 * u.mm,
            nTopForLargeR=1,
            nTopForSmallR=2,
        ),
        useVariableMiddleSPRange=True,
        # deltaRMiddleMinSPRange=10 * u.mm,
        # deltaRMiddleMaxSPRange=10 * u.mm,
        deltaRMiddleSPRange=(1 * u.mm, 10 * u.mm),
    ),
    SeedFinderOptionsArg(bFieldInZ=bFieldZ * u.T,
                         beamPos=(0 * u.mm, 0 * u.mm)),
    SeedFilterConfigArg(
        seedConfirmation=False,
        maxSeedsPerSpMConf=5,
        maxQualitySeedsPerSpMConf=5,
    ),
    SpacePointGridConfigArg(
        # zBinEdges=[
        # -4000.0,
        # -2500.0,
        # -2000.0,
        # -1320.0,
        # -625.0,
        # -350.0,
        # -250.0,
        # 250.0,
        # 350.0,
        # 625.0,
        # 1320.0,
        # 2000.0,
        # 2500.0,
        # 4000.0,
        # ],
        impactMax=3. * u.mm,
        phiBinDeflectionCoverage=3,
    ),
    SeedingAlgorithmConfigArg(
        # zBinNeighborsTop=[
        # [0, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 1],
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 0],
        # ],
        # zBinNeighborsBottom=[
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 1],
        # [0, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # [-1, 0],
        # ],
        # numPhiNeighbors=1,
    ),
    geoSelectionConfigFile=geo_dir /
    "acts/bin/geoSelection-alice3-cfg10.json",
    outputDirRoot=outputDir,
    initialVarInflation=[100, 100, 100, 100, 100, 100],
)
s = addCKFTracks(
    s,
    trackingGeometry,
    field,
    TrackSelectorConfig(pt=(500.0 * u.MeV, None), nMeasurementsMin=7),
    outputDirRoot=outputDir,
    writeTrajectories=True,
)

s = addAmbiguityResolution(
    s,
    AmbiguityResolutionConfig(maximumSharedHits=3),
    outputDirRoot=outputDir,
)

s.run()
